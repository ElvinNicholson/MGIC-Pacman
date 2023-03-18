#include "Inky.h"

Inky::Inky(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr) : Ghost(gameDataPtr)
{
  setTexture(*texture);
  initTextureRects(6);
  setIntRect(textureRects.at(0));
  setScale(2, 2);
  setOriginCentre();
}

void Inky::stateChase()
{
  sf::Vector2i pacTarget;
  sf::Vector2i target;
  float distanceBlinky;

  // Get the tile 2 tiles in front of Pacman
  switch (gameData->pacmanDir)
  {
    case NORTH:
      pacTarget = {gameData->pacmanPos.x, gameData->pacmanPos.y -2};
      break;

    case EAST:
      pacTarget = {gameData->pacmanPos.x + 2, gameData->pacmanPos.y};
      break;

    case SOUTH:
      pacTarget = {gameData->pacmanPos.x, gameData->pacmanPos.y + 2};
      break;

    case WEST:
      pacTarget = {gameData->pacmanPos.x - 2, gameData->pacmanPos.y};
      break;

    case NONE:
      pacTarget = gameData->pacmanPos;
      break;
  }

  // Find the distance between Blinky and pacTarget
  distanceBlinky = pow(pacTarget.x - gameData->blinkyPos.x, 2) + pow(pacTarget.y - gameData->blinkyPos.y, 2);

  target.x = gameData->blinkyPos.x + 2*(pacTarget.x - gameData->blinkyPos.x);

  // Blinky is left of pacTarget
  if (pacTarget.y > gameData->blinkyPos.y)
  {
    target.y = gameData->blinkyPos.y + sqrt(2*distanceBlinky - 2*(pacTarget.y - gameData->blinkyPos.y));
  }
  else
  {
    target.y = gameData->blinkyPos.y - sqrt(2*distanceBlinky - 2*(pacTarget.y - gameData->blinkyPos.y));
  }

  findBestDirection(target);
}

void Inky::resetGhost()
{
  Ghost::resetGhost();
  *next_dir = NORTH;
  *state = WAITING;

  *time_to_release = 18;
}

void Inky::setMap1()
{
  *respawn_destination = {13, 14};
  *dead_destination = {13, 17};
  *scatter_destination = {26, 32};
  *spawn_tile = {12, 17};
  *spawn_offset = 0;

  resetGhost();
}

void Inky::setMap2()
{
  *respawn_destination = {23, 26};
  *dead_destination = {23, 29};
  *scatter_destination = {26, 32};
  *spawn_tile = {23, 29};
  *spawn_offset = 16;

  resetGhost();
}