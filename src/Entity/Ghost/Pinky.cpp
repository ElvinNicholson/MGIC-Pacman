#include "Pinky.h"

Pinky::Pinky(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr) : Ghost(gameDataPtr)
{
  setTexture(*texture);
  initTextureRects(5);
  setIntRect(textureRects.at(0));
  setScale(2, 2);
  setOriginCentre();
}

void Pinky::stateChase()
{
  sf::Vector2i target;

  switch (gameData->pacmanDir)
  {
    case NORTH:
      target = {gameData->pacmanPos.x, gameData->pacmanPos.y -4};
      break;

    case EAST:
      target = {gameData->pacmanPos.x + 4, gameData->pacmanPos.y};
      break;

    case SOUTH:
      target = {gameData->pacmanPos.x, gameData->pacmanPos.y + 4};
      break;

    case WEST:
      target = {gameData->pacmanPos.x - 4, gameData->pacmanPos.y};
      break;

    case NONE:
      target = gameData->pacmanPos;
      break;
  }

  findBestDirection(target);
}

void Pinky::resetGhost()
{
  Ghost::resetGhost();
  *next_dir = SOUTH;
  *state = WAITING;

  *time_to_release = 10;
}

void Pinky::setMap1()
{
  *respawn_destination = {13, 14};
  *dead_destination = {13, 17};
  *scatter_destination = {1, 4};
  *spawn_tile = {14, 17};
  *spawn_offset = 0;

  resetGhost();
}

void Pinky::setMap2()
{
  *respawn_destination = {4, 4};
  *dead_destination = {4, 7};
  *scatter_destination = {1, 4};
  *spawn_tile = {4, 7};
  *spawn_offset = 16;

  resetGhost();
}
