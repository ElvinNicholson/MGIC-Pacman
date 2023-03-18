#include "Ghost.h"

Ghost::Ghost(std::shared_ptr<GameData> gameDataPtr) : Entity(gameDataPtr)
{
  scatter_destination = std::make_unique<sf::Vector2i>();
  dead_destination = std::make_unique<sf::Vector2i>();
  respawn_destination = std::make_unique<sf::Vector2i>();

  time_to_release = std::make_unique<float>();
  spawn_offset = std::make_unique<float>();

  already_frightened = std::make_unique<bool>();
  on_new_tile = std::make_unique<bool>();
  state_timer = std::make_unique<float>();
  state_index = std::make_unique<int>();

  *speed = 200;
  *on_new_tile = true;
  *already_frightened = false;

  state_pattern = {5, 20, 5, 20, 5, 20, 5, 20};
}

void Ghost::updateGhost(float dt)
{
  if (*on_new_tile)
  {
    switch (*state)
    {
      case CHASE:
        stateChase();
        break;

      case SCATTER:
        stateScatter();
        break;

      case DEAD:
        stateDead();
        break;

      case FRIGHTENED:
        stateFright();
        break;

      case RESPAWNING:
        stateRespawn();
        break;

      case WAITING:
        stateWaiting();

      default:
        break;
    }

    *on_new_tile = false;
  }

  playAnimation(dt);
  stateManager(dt);

  sf::Vector2i lastPos = getTilePos();
  moveEntity(dt);
  if (lastPos != getTilePos())
  {
    *on_new_tile = true;
  }
}

void Ghost::stateScatter()
{
  findBestDirection(*scatter_destination);
}

void Ghost::stateDead()
{
  *speed = 500;
  findBestDirection(*dead_destination);

  // Switch to RESPAWNING state when ghost reaches its home
  if (*dead_destination == getTilePos())
  {
    *state = RESPAWNING;
  }
}

void Ghost::stateFright()
{
  getRandomDirection();
}

void Ghost::stateRespawn()
{
  *speed = 200;
  findBestDirection(*respawn_destination);

  // Switch to SCATTER state when ghost fully respawns
  if (*respawn_destination == getTilePos())
  {
    *state = SCATTER;
  }
}

void Ghost::stateWaiting()
{
  sf::Vector2i tile;
  findAdjacentTiles(*current_dir, tile);

  *speed = 100;

  if (!checkWallCollision(tile))
  {
    if (*current_dir == NORTH)
    {
      *next_dir = SOUTH;
    }
    else
    {
      *next_dir = NORTH;
    }
  }
}

void Ghost::initTextureRects(int y_pos)
{
  textureRects.reserve(16);
  // Normal state
  for (int i = 0; i < 8; i++)
  {
    textureRects.emplace_back(sf::IntRect(32*i, y_pos*32, 32, 32));
  }

  // Frightened state
  textureRects.emplace_back(sf::IntRect(256, 128, 32, 32));
  textureRects.emplace_back(sf::IntRect(288, 128, 32, 32));
  textureRects.emplace_back(sf::IntRect(320, 128, 32, 32));

  // Dead state
  for (int i = 0; i < 4; i++)
  {
    textureRects.emplace_back(sf::IntRect(256 + (32*i), 160, 32, 32));
  }

  // Score
  textureRects.emplace_back(sf::IntRect(384, 127, 32, 32));
}

void Ghost::findBestDirection(sf::Vector2i destination)
{
  float distances[4] = {9999, 9999, 9999, 9999};

  // Check if North is not a wall
  sf::Vector2i northTile = {getTilePos().x, getTilePos().y - 1};
  if (checkWallCollision(northTile) && *current_dir != SOUTH)
  {
    distances[0] = pow(northTile.x - destination.x, 2.0) + pow(northTile.y - destination.y, 2.0);
  }

  // Check if East is not a wall
  sf::Vector2i eastTile = {getTilePos().x + 1, getTilePos().y};
  if (checkWallCollision(eastTile) && *current_dir != WEST)
  {
    distances[1] = pow(eastTile.x - destination.x, 2.0) + pow(eastTile.y - destination.y, 2.0);
  }

  // Check if South is not a wall
  sf::Vector2i southTile = {getTilePos().x, getTilePos().y + 1};
  if (checkWallCollision(southTile) && *current_dir != NORTH)
  {
    distances[2] = pow(southTile.x - destination.x, 2.0) + pow(southTile.y - destination.y, 2.0);
  }

  // Check if West is not a wall
  sf::Vector2i westTile = {getTilePos().x - 1, getTilePos().y};
  if (checkWallCollision(westTile) && *current_dir != EAST)
  {
    distances[3] = pow(westTile.x - destination.x, 2.0) + pow(westTile.y - destination.y, 2.0);
  }

  // Find the lowest distance
  float lowestVal = INT_MAX;
  int lowestIndex = 0;

  for (int i = 0; i < 4; i++)
  {
    if (lowestVal > distances[i])
    {
      lowestVal = distances[i];
      lowestIndex = i;
    }
  }

  // Set the next direction as the shortest distance
  switch (lowestIndex)
  {
    case 0:
      *next_dir = NORTH;
      break;

    case 1:
      *next_dir = EAST;
      break;

    case 2:
      *next_dir = SOUTH;
      break;

    case 3:
      *next_dir = WEST;
      break;

    default:
      *next_dir = NORTH;
      break;
  }
}

void Ghost::getRandomDirection()
{
  std::vector<Direction> valid_directions;
  valid_directions.reserve(3);

  // Check if North is not a wall
  sf::Vector2i northTile = {getTilePos().x, getTilePos().y - 1};
  if (checkWallCollision(northTile) && *current_dir != SOUTH)
  {
    valid_directions.push_back(NORTH);
  }

  // Check if East is not a wall
  sf::Vector2i eastTile = {getTilePos().x + 1, getTilePos().y};
  if (checkWallCollision(eastTile) && *current_dir != WEST)
  {
    valid_directions.push_back(EAST);
  }

  // Check if South is not a wall
  sf::Vector2i southTile = {getTilePos().x, getTilePos().y + 1};
  if (checkWallCollision(southTile) && *current_dir != NORTH)
  {
    valid_directions.push_back(SOUTH);
  }

  // Check if West is not a wall
  sf::Vector2i westTile = {getTilePos().x - 1, getTilePos().y};
  if (checkWallCollision(westTile) && *current_dir != EAST)
  {
    valid_directions.push_back(WEST);
  }

  // Use random number to pick a valid direction
  int random_num = rand() % (valid_directions.size());
  *next_dir = valid_directions.at(random_num);
}

void Ghost::playAnimation(float dt)
{
  *frame_time -= dt;

  if (*frame_time < 0)
  {
    *frame_time = 0.18;
    *frame_index += 1;
    *frame_index = std::clamp(*frame_index, 0, 15);
  }

  switch(*state)
  {
    case RESPAWNING:
    case SCATTER:
    case CHASE:
    case WAITING:
      animationMoving();
      break;

    case DEAD:
      animationDead();
      break;

    case FRIGHTENED:
      animationFrightened();
      break;

    default:
      break;
  }

  setIntRect(textureRects.at(*frame_index));
}

void Ghost::animationMoving()
{
  switch (*current_dir)
  {
    case NORTH:
      if (4 > *frame_index || *frame_index > 5)
      {
        *frame_index = 4;
      }
      break;

    case EAST:
      if (0 > *frame_index || *frame_index > 1)
      {
        *frame_index = 0;
      }
      break;

    case SOUTH:
      if (6 > *frame_index || *frame_index > 7)
      {
        *frame_index = 6;
      }
      break;

    case WEST:
      if (2 > *frame_index || *frame_index > 3)
      {
        *frame_index = 2;
      }
      break;

    default:
      break;
  }
}

void Ghost::animationDead()
{
  switch (*current_dir)
  {
    case NORTH:
      *frame_index = 13;
      break;

    case EAST:
      *frame_index = 11;
      break;

    case SOUTH:
      *frame_index = 14;
      break;

    case WEST:
      *frame_index = 12;
      break;

    default:
      break;
  }
}

void Ghost::animationFrightened()
{
  if (gameData->pacmanPoweredTime > 3)
  {
    if (8 > *frame_index || *frame_index > 9)
    {
      *frame_index = 8;
    }
  }
  else
  {
    if (9 > *frame_index || *frame_index > 10)
    {
      *frame_index = 9;
    }
  }
}

void Ghost::stateManager(float dt)
{
  // Follows state pattern
  if (*state_index < 7)
  {
    *state_timer -= dt;

    if (*state_timer < 0)
    {
      *state_index += 1;
      *state_timer = state_pattern.at(*state_index);
    }
  }

  if ((*state_index == 0 || *state_index == 2 ||
       *state_index == 4 || *state_index == 6) &&
       *state == CHASE)
  {
    *state = SCATTER;
  }
  else if ((*state_index == 1 || *state_index == 3 ||
            *state_index == 5 || *state_index == 7) &&
            *state == SCATTER)
  {
    *state = CHASE;
  }

  // Release Ghost
  if (*state == WAITING)
  {
    *time_to_release -= dt;

    if (*time_to_release < 0)
    {
      *state = RESPAWNING;
    }
  }

  // Frightened state
  if (gameData->pacmanPowered && !*already_frightened)
  {
    if (*state != DEAD && *state != RESPAWNING && *state != WAITING)
    {
      *state = FRIGHTENED;
      *speed = 100;
    }
    *already_frightened = true;
  }
  else if(!gameData->pacmanPowered)
  {
    if (*state == FRIGHTENED)
    {
      *state = SCATTER;
      *speed = 200;
    }
    *already_frightened = false;
  }
}

void Ghost::frighten()
{
  *already_frightened = false;
}

void Ghost::setState(EntityState newState)
{
  *state = newState;
  *on_new_tile = true;
}

void Ghost::killGhost()
{
  setState(DEAD);
  setIntRect(textureRects.at(15));
}

void Ghost::resetGhost()
{
  *frame_index = 0;
  *state_index = 0;
  *state_timer = state_pattern.at(*state_index);

  setIntRect(textureRects.at(0));
  *speed = 200;

  *on_new_tile = true;
  *already_frightened = false;

  *current_dir = NONE;
  *next_dir = NONE;
  *next_destination = *spawn_tile;
  *current_destination = *spawn_tile;
  setPosition(spawn_tile->x * 32 + *spawn_offset, spawn_tile->y * 32 + 16);
}
