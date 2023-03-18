#ifndef PACMANSFML_GAMEDATA_H
#define PACMANSFML_GAMEDATA_H

// External Library
#include <SFML/Graphics.hpp>
#include "tmxlite/TileLayer.hpp"

// Game Codebase
#include "Entity/Direction.h"
#include "Audio/AudioManager.h"
#include "Tiles/Tilemap.h"

class GameData
{
 public:
  sf::Vector2i pacmanPos;
  Direction pacmanDir;
  bool pacmanPowered;
  float pacmanPoweredTime;

  sf::Vector2i blinkyPos;

  std::unique_ptr<Tilemap> tilemap;

 protected:

 private:

};

#endif // PACMANSFML_GAMEDATA_H
