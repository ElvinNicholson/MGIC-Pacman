#ifndef PACMANSFML_AUDIOMANAGER_H
#define PACMANSFML_AUDIOMANAGER_H

// Standard Library
#include <iostream>

// External Library
#include <SFML/Audio.hpp>

class AudioManager
{
 public:
  AudioManager();

  void ghostSoundManager(bool isGhostFrightened, bool isGhostDead, bool pause);

  float playIntro();
  void playMunch();
  float playEatGhost();
  void playDeath();
  float playWin();

 private:
  std::unique_ptr<sf::SoundBuffer> introBuffer;
  std::unique_ptr<sf::Sound> introSound;

  std::unique_ptr<sf::SoundBuffer> munch1Buffer;
  std::unique_ptr<sf::Sound> munch1Sound;
  std::unique_ptr<bool> munch1_played;

  std::unique_ptr<sf::SoundBuffer> munch2Buffer;
  std::unique_ptr<sf::Sound> munch2Sound;

  std::unique_ptr<sf::SoundBuffer> eatGhostBuffer;
  std::unique_ptr<sf::Sound> eatGhostSound;

  std::unique_ptr<sf::SoundBuffer> deathBuffer;
  std::unique_ptr<sf::Sound> deathSound;

  std::unique_ptr<sf::SoundBuffer> powerBuffer;
  std::unique_ptr<sf::Sound> powerSound;

  std::unique_ptr<sf::SoundBuffer> retreatBuffer;
  std::unique_ptr<sf::Sound> retreatSound;

  std::unique_ptr<sf::SoundBuffer> ghostBuffer;
  std::unique_ptr<sf::Sound> ghostSound;

  std::unique_ptr<sf::SoundBuffer> winBuffer;
  std::unique_ptr<sf::Sound> winSound;

 protected:

};

#endif // PACMANSFML_AUDIOMANAGER_H
