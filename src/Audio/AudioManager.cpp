#include "AudioManager.h"

AudioManager::AudioManager()
{
  introBuffer = std::make_unique<sf::SoundBuffer>();
  introBuffer->loadFromFile("../Data/Audio/game_start.wav");
  introSound = std::make_unique<sf::Sound>();
  introSound->setBuffer(*introBuffer);

  munch1Buffer = std::make_unique<sf::SoundBuffer>();
  munch1Buffer->loadFromFile("../Data/Audio/munch_1.wav");
  munch1Sound = std::make_unique<sf::Sound>();
  munch1Sound->setBuffer(*munch1Buffer);
  munch1_played = std::make_unique<bool>();
  *munch1_played = false;

  munch2Buffer = std::make_unique<sf::SoundBuffer>();
  munch2Buffer->loadFromFile("../Data/Audio/munch_2.wav");
  munch2Sound = std::make_unique<sf::Sound>();
  munch2Sound->setBuffer(*munch2Buffer);

  eatGhostBuffer = std::make_unique<sf::SoundBuffer>();
  eatGhostBuffer->loadFromFile("../Data/Audio/eat_ghost.wav");
  eatGhostSound = std::make_unique<sf::Sound>();
  eatGhostSound->setBuffer(*eatGhostBuffer);

  deathBuffer = std::make_unique<sf::SoundBuffer>();
  deathBuffer->loadFromFile("../Data/Audio/death_1.wav");
  deathSound = std::make_unique<sf::Sound>();
  deathSound->setBuffer(*deathBuffer);

  powerBuffer = std::make_unique<sf::SoundBuffer>();
  powerBuffer->loadFromFile("../Data/Audio/power_pellet.wav");
  powerSound = std::make_unique<sf::Sound>();
  powerSound->setBuffer(*powerBuffer);
  powerSound->setLoop(true);

  retreatBuffer = std::make_unique<sf::SoundBuffer>();
  retreatBuffer->loadFromFile("../Data/Audio/retreating.wav");
  retreatSound = std::make_unique<sf::Sound>();
  retreatSound->setBuffer(*retreatBuffer);
  retreatSound->setLoop(true);

  ghostBuffer = std::make_unique<sf::SoundBuffer>();
  ghostBuffer->loadFromFile("../Data/Audio/siren_1.wav");
  ghostSound = std::make_unique<sf::Sound>();
  ghostSound->setBuffer(*ghostBuffer);
  ghostSound->setLoop(true);

  winBuffer = std::make_unique<sf::SoundBuffer>();
  winBuffer->loadFromFile("../Data/Audio/intermission.wav");
  winSound = std::make_unique<sf::Sound>();
  winSound->setBuffer(*winBuffer);
}

void AudioManager::ghostSoundManager(bool isGhostFrightened, bool isGhostDead, bool pause)
{
  if (pause || deathSound->getStatus() == sf::SoundSource::Playing)
  {
    ghostSound->pause();
    powerSound->pause();
    retreatSound->pause();
    return;
  }

  if (!isGhostFrightened && !isGhostDead && ghostSound->getStatus() != sf::SoundSource::Playing)
  {
    ghostSound->play();
    powerSound->pause();
    retreatSound->pause();
  }
  else if (isGhostFrightened && !isGhostDead && powerSound->getStatus() != sf::SoundSource::Playing)
  {
    powerSound->play();
    ghostSound->pause();
    retreatSound->pause();
  }
  else if (isGhostDead && retreatSound->getStatus() != sf::SoundSource::Playing)
  {
    retreatSound->play();
    ghostSound->pause();
    powerSound->pause();
  }
}

float AudioManager::playIntro()
{
  introSound->play();
  return introBuffer->getDuration().asSeconds();
}

void AudioManager::playMunch()
{
  if (!*munch1_played)
  {
    munch1Sound->play();
    *munch1_played = true;
    return;
  }
  munch2Sound->play();
  *munch1_played = false;
}

float AudioManager::playEatGhost()
{
  eatGhostSound->play();
  return eatGhostBuffer->getDuration().asSeconds();
}

void AudioManager::playDeath()
{
  deathSound->play();
}

float AudioManager::playWin()
{
  winSound->play();
  return winBuffer->getDuration().asSeconds();
}
