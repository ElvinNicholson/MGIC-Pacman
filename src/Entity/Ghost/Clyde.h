#ifndef PACMANSFML_CLYDE_H
#define PACMANSFML_CLYDE_H

// Game Codebase
#include "Ghost.h"

class Clyde : public Ghost
{
 public:
  Clyde(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr);
  void resetGhost() override;
  void setMap1() override;
  void setMap2() override;

 protected:

 private:
  void stateChase() override;
};

#endif // PACMANSFML_CLYDE_H
