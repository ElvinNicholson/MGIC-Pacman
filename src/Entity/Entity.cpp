#include "Entity.h"

Entity::Entity(std::shared_ptr<GameData> gameDataPtr) : gameData(gameDataPtr)
{
  current_dir = std::make_unique<Direction>();
  next_dir = std::make_unique<Direction>();

  current_destination = std::make_unique<sf::Vector2i>();
  next_destination = std::make_unique<sf::Vector2i>();
  spawn_tile = std::make_unique<sf::Vector2i>();

  state = std::make_unique<EntityState>();

  speed = std::make_unique<float>();
  frame_time = std::make_unique<float>();
  frame_index = std::make_unique<int>();

  *frame_time = 0;
  *frame_index = 0;
}

void Entity::moveEntity(float dt)
{
  // Find which tile is the next destination
  findAdjacentTiles(*next_dir, *next_destination);

  // Set new direction if its valid
  if (*next_dir != *current_dir && checkWallCollision(*next_destination))
  {
    *current_dir = *next_dir;

    // Position entity to centre of tile
    if ((*current_dir == NORTH || *current_dir == SOUTH) && *state != WAITING)
    {
      setPosition(next_destination->x * 32 + 16, getPosition().y);
    }
    else if (*current_dir == EAST || *current_dir == WEST)
    {
      setPosition(getPosition().x, next_destination->y * 32 + 16);
    }
  }

  // Find which tile is the current destination
  findAdjacentTiles(*current_dir, *current_destination);

  // Check if current destination is a wall, if not a wall move
  if (checkWallCollision(*current_destination))
  {
    switch (*current_dir)
    {
      case NORTH:
        move(0, - *speed * dt);
        break;

      case EAST:
        move(*speed * dt, 0);
        break;

      case SOUTH:
        move(0, *speed * dt);
        break;

      case WEST:
        move(- *speed * dt, 0);
        break;

      default:
        break;
    }
  }
  else
  {
    setPosition(getTilePos().x * 32 + 16, getTilePos().y * 32 + 16);
    *current_dir = NONE;
  }

  // Portal
  portal();
}

bool Entity::checkWallCollision(sf::Vector2i tilePos)
{
  if (*gameData->tilemap->getTilemap().at(tilePos.y * 28 + tilePos.x)->tile_id == 12 ||
      tilePos == sf::Vector2i(-1, 17) ||
      tilePos == sf::Vector2i(28, 17) ||
      ((*gameData->tilemap->getTilemap().at(tilePos.y * 28 + tilePos.x)->tile_id == 11) && (*state == DEAD || *state == RESPAWNING)))
  {
    return true;
  }
  return false;
}

void Entity::findAdjacentTiles(Direction direction, sf::Vector2i& destination)
{
  switch (direction)
  {
    case NORTH:
      destination = {getTilePos().x, getTilePos().y - 1};
      break;

    case EAST:
      destination = {getTilePos().x + 1, getTilePos().y};
      break;

    case SOUTH:
      destination = {getTilePos().x, getTilePos().y + 1};
      break;

    case WEST:
      destination = {getTilePos().x - 1, getTilePos().y};
      break;

    default:
      break;
  }
}

void Entity::portal()
{
  // Left portal
  if (*current_destination == sf::Vector2i(-1, 17))
  {
    *next_destination = {27,17};
    *current_destination = *next_destination;
    setPosition(864, 560);
  }
  // Right portal
  else if (*current_destination == sf::Vector2i(28, 17))
  {
    *next_destination = {0, 17};
    *current_destination = *next_destination;
    setPosition(0, 560);
  }
}

void Entity::setState(EntityState newState)
{
  *state = newState;
}

EntityState Entity::getState()
{
  return *state;
}

Direction Entity::getDirection()
{
  return *current_dir;
}
