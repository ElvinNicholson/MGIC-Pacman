#ifndef PACMANSFML_PINKY_H
#define PACMANSFML_PINKY_H

// Game Codebase
#include "Ghost.h"

class Pinky : public Ghost
{
 public:
  Pinky(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr);
  void resetGhost() override;
  void setMap1() override;
  void setMap2() override;

 protected:

 private:
  void stateChase() override;
};

#endif // PACMANSFML_PINKY_H
