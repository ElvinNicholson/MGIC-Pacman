#ifndef PACMANSFML_INKY_H
#define PACMANSFML_INKY_H

// Game Codebase
#include "Ghost.h"

class Inky : public Ghost
{
 public:
  Inky(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr);
  void resetGhost() override;
  void setMap1() override;
  void setMap2() override;

 protected:

 private:
  void stateChase() override;
};

#endif // PACMANSFML_INKY_H
