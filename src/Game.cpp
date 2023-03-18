
#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  gamestate = std::make_shared<States>();
  *gamestate = TITLE;

  last_state = std::make_unique<States>();
  *last_state = *gamestate;

  selected_map = std::make_unique<int>();
  title = std::make_unique<Title>(gamestate, selected_map);
  gameplay = std::make_unique<Gameplay>(gamestate);

  return true;
}

void Game::update(float dt)
{
  switch (*gamestate)
  {
    case TITLE:
      isStateChanged();
      title->update(dt);
      break;

    case GAMEPLAY:
      if (isStateChanged())
      {
        switch (*selected_map)
        {
          case 1:
            gameplay->setMap1();
            break;

          case 2:
            gameplay->setMap2();
            break;

          default:
            break;
        }
        is_map_loaded = true;
      }

      gameplay->update(dt);
      break;
  }
}

void Game::render()
{
    window.clear(sf::Color(255, 223, 0));

    switch (*gamestate)
    {
      case TITLE:
        title->render(window);
        break;

      case GAMEPLAY:
        if (!is_map_loaded)
        {
          return;
        }
        gameplay->render(window);
        break;
    }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  switch (*gamestate)
  {
    case TITLE:
      title->eventHandler(event);
      break;

    case GAMEPLAY:
      break;
  }
}

bool Game::isStateChanged()
{
  if (*last_state != *gamestate)
  {
    *last_state = *gamestate;
    return true;
  }
  return false;
}
