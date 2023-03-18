#include "Gameplay.h"

Gameplay::Gameplay(std::shared_ptr<States> _gamestate) : Gamestate(_gamestate)
{
  pause = std::make_unique<bool>();
  is_game_started = std::make_unique<bool>();
  is_pacman_dying = std::make_unique<bool>();
  pause_timer = std::make_unique<float>();
  current_score = std::make_unique<int>();
  high_score = std::make_unique<int>();
  lives = std::make_unique<int>();
  map = std::make_unique<int>();
  ghost_eaten = std::make_unique<int>();

  entityTexture = std::make_unique<sf::Texture>();
  entityTexture->loadFromFile("../Data/Images/Entity.png");

  audioManager = std::make_unique<AudioManager>();

  gameData = std::make_shared<GameData>();

  pacman = std::make_unique<Pacman>(entityTexture, gameData);

  ghosts.reserve(4);
  ghosts.emplace_back(std::make_unique<Blinky>(entityTexture, gameData));
  ghosts.emplace_back(std::make_unique<Pinky>(entityTexture, gameData));
  ghosts.emplace_back(std::make_unique<Inky>(entityTexture, gameData));
  ghosts.emplace_back(std::make_unique<Clyde>(entityTexture, gameData));

  initAllText();

  lives_counter = std::make_unique<GameObject>();
  lives_counter->setTexture(*entityTexture);
  lives_counter->setPosition(32, 1096);
  lives_counter->setScale(1.5, 1.5);
}

void Gameplay::update(float dt)
{
  if (!*is_game_started)
  {
    setMidText("Ready!", sf::Color(255, 255, 0));
    pauseGame(audioManager->playIntro());
    *is_game_started = true;
  }

  audioManager->ghostSoundManager(isGhostOnState(FRIGHTENED), isGhostOnState(DEAD), *pause);

  if (pauseManager(dt))
  {
    return;
  }

  if (middle_text->getString() == "Ready!")
  {
    setMidText("");
  }

  entityManager(dt);
  collectibleManager();
}

void Gameplay::render(sf::RenderWindow& window)
{
  for (auto& tileSprite : gameData->tilemap->getTilemap())
  {
      tileSprite->renderObject(window);
  }

  for (auto& item : collectibles)
  {
    item.renderObject(window);
  }

  pacman -> renderObject(window);

  if (!*is_pacman_dying)
  {
    for (auto& ghost : ghosts)
    {
        ghost->renderObject(window);
    }
  }

  window.draw(*current_score_text);
  window.draw(*current_score_number);
  window.draw(*high_score_text);
  window.draw(*high_score_number);
  window.draw(*middle_text);

  lives_counter->renderObject(window);
}

void Gameplay::eventHandler(sf::Event event)
{

}

void Gameplay::setMap1()
{
  *map = 1;
  gameData->tilemap = std::make_unique<Tilemap>("../Data/Tilemap/MazeMap.tmx");

  pacman->setMap1();

  for (auto& ghost : ghosts)
  {
      ghost->setMap1();
  }

  resetGame();
}

void Gameplay::setMap2()
{
  *map = 2;
  gameData->tilemap = std::make_unique<Tilemap>("../Data/Tilemap/MazeMap2.tmx");

  pacman->setMap2();

  for (auto& ghost : ghosts)
  {
      ghost->setMap2();
  }

  resetGame();
}

void Gameplay::initAllText()
{
  font = std::make_unique<sf::Font>();
  font->loadFromFile("../Data/Fonts/GravityBold8.ttf");

  *current_score = 0;

  high_score_text = std::make_unique<sf::Text>();
  high_score_text->setFont(*font);
  high_score_text->setCharacterSize(24);
  high_score_text->setFillColor(sf::Color::White);
  high_score_text->setString("HIGH SCORE");
  high_score_text->setPosition(448 - high_score_text->getGlobalBounds().width/2, 8);

  high_score_number = std::make_unique<sf::Text>();
  high_score_number->setFont(*font);
  high_score_number->setCharacterSize(24);
  high_score_number->setFillColor(sf::Color::White);
  readHighScore();

  current_score_text = std::make_unique<sf::Text>();
  current_score_text->setFont(*font);
  current_score_text->setCharacterSize(24);
  current_score_text->setFillColor(sf::Color::White);
  current_score_text->setString("SCORE");
  current_score_text->setPosition(210 - current_score_text->getGlobalBounds().width, 8);

  current_score_number = std::make_unique<sf::Text>();
  current_score_number->setFont(*font);
  current_score_number->setCharacterSize(24);
  current_score_number->setFillColor(sf::Color::White);
  updateScore(0);

  middle_text = std::make_unique<sf::Text>();
  middle_text->setFont(*font);
  middle_text->setCharacterSize(24);
}

void Gameplay::placeCollectibles()
{
  collectibles.reserve(gameData->tilemap->getCollectibleMap().size());

  int idx;
  int idy;
  int index = 0;

  for (auto& item : gameData->tilemap->getCollectibleMap())
  {
    idx = index / 28;
    idy = index % 28;

    switch (item)
    {
      case 1:
        //Normal Pellet
        collectibles.emplace_back(Collectible(entityTexture, NORMAL_PELLET));
        collectibles.back().setPosition(idy * 32 + 16, idx * 32 + 16);
        break;

      case 2:
        //Power Pellet
        collectibles.emplace_back(entityTexture, POWER_PELLET);
        collectibles.back().setPosition(idy * 32 + 16, idx * 32 + 16);
        break;

      default:
        break;
    }
    index++;
  }
}

void Gameplay::resetLevel()
{
  *pause = false;
  *is_pacman_dying = false;

  pacman->resetPacman();

  for (auto& ghost : ghosts)
  {
      ghost->resetGhost();
  }
}

void Gameplay::resetGame()
{
  resetLevel();

  *is_game_started = false;

  *current_score = 0;
  updateScore(0);

  *lives = 3;
  updateLivesCounter();

  collectibles.clear();
  placeCollectibles();

  *ghost_eaten = 0;
}

void Gameplay::entityManager(float dt)
{
  if (pacman->isDeadAnimationDone())
  {
    resetLevel();
    checkLives();
    return;
  }

  // Update Entity
  pacman -> updatePacman(dt);

  for (auto& ghost : ghosts)
  {
      ghost->updateGhost(dt);
  }
  gameData->blinkyPos = ghosts.at(0)->getTilePos();

  for (auto& ghost : ghosts)
  {
      if (pointCollision(pacman->getPosition(), ghost->getGlobalBounds()))
      {
          if (gameData->pacmanPowered && ghost->getState() == FRIGHTENED)
          {
              ghost->killGhost();
              updateScore(200);
              pauseGame(audioManager->playEatGhost());
              placeFruit();
          }
          else if (pacman->getState() != DEAD && ghost->getState() != DEAD)
          {
              killPacman();
          }
      }
  }
}

void Gameplay::collectibleManager()
{
  for (int i = 0; i < collectibles.size(); i++)
  {
    if (pacman->getTilePos() == collectibles[i].getTilePos())
    {
      if (*collectibles[i].type == POWER_PELLET)
      {
        pacman->powerUp();

        for (auto& ghost : ghosts)
        {
            ghost->frighten();
        }
      }

      updateScore(*collectibles[i].points);
      collectibles.erase(collectibles.begin()+i);
      audioManager->playMunch();

      if (collectibles.empty())
      {
        setMidText("GAME WON!", sf::Color(255, 255, 0));
        pauseGame(audioManager->playWin());
        writeHighScore();
      }
    }
  }
}

bool Gameplay::pauseManager(float dt)
{
  if (*pause)
  {
    *pause_timer -= dt;
    if (*pause_timer < 0)
    {
      *pause = false;

      checkPellets();
      if (pacman->getState() == DEAD)
      {
        *is_pacman_dying = true;
        audioManager->playDeath();
      }
    }
    return true;
  }
  return false;
}

void Gameplay::pauseGame(float pause_time)
{
  *pause = true;
  *pause_timer = pause_time;
}

void Gameplay::updateScore(int points)
{
  *current_score += points;
  current_score_number->setString(std::to_string(*current_score));
  current_score_number->setPosition(210 - current_score_number->getGlobalBounds().width, 40);

  if (*current_score > *high_score)
  {
    *high_score = *current_score;
    updateHighScore();
  }
}

void Gameplay::updateHighScore()
{
  high_score_number->setString(std::to_string(*high_score));
  high_score_number->setPosition(448 - high_score_number->getGlobalBounds().width/2, 40);
}

void Gameplay::updateLivesCounter()
{
  lives_counter->setIntRect(sf::IntRect(384, 32, (*lives - 1) * 32, 32));
}

bool Gameplay::isGhostOnState(EntityState state)
{
    for (auto& ghost : ghosts)
    {
        if (ghost->getState() == state)
        {
          return true;
         }
    }
    return false;
}

bool Gameplay::pointCollision(sf::Vector2f point, sf::FloatRect object)
{
  if (object.left < point.x &&
      object.left + object.width > point.x &&
      object.top < point.y &&
      object.top + object.height > point.y)
  {
    return true;
  }
  return false;
}

void Gameplay::killPacman()
{
  pacman->setState(DEAD);
  *lives -= 1;
  updateLivesCounter();

  if (*lives == 0)
  {
    setMidText("Game Over!", sf::Color(255, 0, 0));
    writeHighScore();
  }
  pauseGame(1.5);
}

void Gameplay::checkLives()
{
  if (*lives == 0)
  {
    *gamestate = TITLE;
  }
}

void Gameplay::checkPellets()
{
  if (collectibles.empty())
  {
    *gamestate = TITLE;
  }
}

void Gameplay::setMidText(std::string string, sf::Color color)
{
  middle_text->setFillColor(color);
  middle_text->setString(string);
  middle_text->setPosition(448 - middle_text->getGlobalBounds().width/2, 676 - *map * 32);
}

void Gameplay::placeFruit()
{
  *ghost_eaten += 1;
  switch (*ghost_eaten)
  {
    case 2:
      collectibles.emplace_back(entityTexture, CHERRY);
      if (*map == 1)
      {
        collectibles.back().setPosition(14 * 32, 26 * 32 + 16);
        return;
      }
      collectibles.back().setPosition(14 * 32, 16 * 32 + 16);
      break;

    case 6:
      collectibles.emplace_back(entityTexture, ORANGE);
      if (*map == 1)
      {
        collectibles.back().setPosition(14 * 32, 20 * 32 + 16);
        return;
      }
      collectibles.back().setPosition(4 * 32 + 16, 26 * 32 + 16);
      break;

    case 10:
      collectibles.emplace_back(entityTexture, MELON);
      if (*map == 1)
      {
        collectibles.back().setPosition(14 * 32, 14 * 32 + 16);
        return;
      }
      collectibles.back().setPosition(23 * 32 + 16, 26 * 32 + 16);
      break;
  }
}

void Gameplay::readHighScore()
{
  std::string score_text;
  std::ifstream score_file("../Data/Other/HighScore.txt");

  int index = 0;
  while (std::getline(score_file, score_text))
  {
    if (index == *map - 1)
    {
      *high_score = std::stoi(score_text);
      break;
    }
    index++;
  }

  score_file.close();
  updateHighScore();
}

void Gameplay::writeHighScore()
{
  std::string score_1;
  std::string score_2;
  std::string current_line;

  std::ifstream in_file("../Data/Other/HighScore.txt");

  int index = 0;
  while (std::getline(in_file, current_line))
  {
    switch (index)
    {
      case 0:
        score_1 = current_line;
        break;

      case 1:
        score_2 = current_line;
        break;

      default:
        break;
    }
    index++;
  }

  in_file.close();

  std::ofstream out_file("../Data/Other/HighScore.txt");

  switch (*map)
  {
    case 1:
      score_1 = std::to_string(*high_score);
      break;

    case 2:
      score_2 = std::to_string(*high_score);
      break;
  }

  out_file << score_1 + "\n";
  out_file << score_2 + "\n";

  out_file.close();
}
