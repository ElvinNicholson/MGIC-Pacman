#ifndef PACMANSFML_BLINKY_H
#define PACMANSFML_BLINKY_H

// Game Codebase
#include "Ghost.h"

class Blinky : public Ghost
{
 public:
  Blinky(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr);
  void resetGhost() override;
  void setMap1() override;
  void setMap2() override;

 protected:

 private:
  void stateChase() override;
};

#endif // PACMANSFML_BLINKY_H
