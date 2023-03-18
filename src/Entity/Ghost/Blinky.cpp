#include "Blinky.h"

Blinky::Blinky(std::unique_ptr<sf::Texture>& texture, std::shared_ptr<GameData> gameDataPtr) : Ghost(gameDataPtr)
{
  setTexture(*texture);
  initTextureRects(4);
  setIntRect(textureRects.at(0));
  setScale(2, 2);
  setOriginCentre();
}

void Blinky::stateChase()
{
  findBestDirection(gameData->pacmanPos);
}

void Blinky::resetGhost()
{
  Ghost::resetGhost();
  *state = SCATTER;
}

void Blinky::setMap1()
{
  *respawn_destination = {13, 14};
  *dead_destination = {13, 17};
  *scatter_destination = {26, 4};
  *spawn_tile = {14, 14};
  *spawn_offset = 0;

  resetGhost();
}

void Blinky::setMap2()
{
  *respawn_destination = {23, 4};
  *dead_destination = {23, 7};
  *scatter_destination = {26, 4};
  *spawn_tile = {23, 4};
  *spawn_offset = 16;

  resetGhost();
}
