#include "Clyde.h"

Clyde::Clyde(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr) : Ghost(gameDataPtr)
{
  setTexture(*texture);
  initTextureRects(7);
  setIntRect(textureRects.at(0));
  setScale(2, 2);
  setOriginCentre();
}

void Clyde::stateChase()
{
  float distancePac;

  // Get distance between Pacman and Clyde
  distancePac = sqrt(pow(getTilePos().x - gameData->pacmanPos.x, 2) + pow(getTilePos().y - gameData->pacmanPos.y, 2));

  if (distancePac > 8)
  {
    findBestDirection(gameData->pacmanPos);
  }
  else
  {
    findBestDirection(*scatter_destination);
  }
}

void Clyde::resetGhost()
{
  Ghost::resetGhost();
  *next_dir = NORTH;
  *state = WAITING;

  *time_to_release = 25;
}

void Clyde::setMap1()
{
  *respawn_destination = {13, 14};
  *dead_destination = {13, 17};
  *scatter_destination = {1, 32};
  *spawn_tile = {16, 17};
  *spawn_offset = 0;

  resetGhost();
}

void Clyde::setMap2()
{
  *respawn_destination = {4, 26};
  *dead_destination = {4, 29};
  *scatter_destination = {1, 32};
  *spawn_tile = {4, 29};
  *spawn_offset = 16;

  resetGhost();
}
