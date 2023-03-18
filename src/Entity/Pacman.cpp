#include "Pacman.h"

Pacman::Pacman(std::unique_ptr<sf::Texture> &texture, std::shared_ptr<GameData> gameDataPtr) : Entity(gameDataPtr)
{
  is_powered = std::make_unique<bool>();
  power_timer = std::make_unique<float>();

  setTexture(*texture);
  textureRects.reserve(14);

  for (int i = 0; i < 14; i++)
  {
    textureRects.emplace_back(sf::IntRect(32*i, 0, 32, 32));
  }

  setIntRect(textureRects.at(2));
  setScale(2, 2);
  setOriginCentre();

  *speed = 250;
}

void Pacman::updatePacman(float dt)
{
  gameData->pacmanPos = getTilePos();
  gameData->pacmanDir = getDirection();
  gameData->pacmanPowered = *is_powered;

  changeState(dt);
  playAnimation(dt);

  if (*state != DEAD)
  {
    playerControl();
    moveEntity(dt);
  }
}

void Pacman::changeState(float dt)
{
  if (*is_powered)
  {
    *power_timer -= dt;

    if (*power_timer < 0)
    {
      *is_powered = false;
      *power_timer = 10;
    }

    gameData->pacmanPoweredTime = *power_timer;
  }

  if (*state != DEAD)
  {
    switch (*current_dir)
    {
      case NONE:
        *state = IDLE;
        break;

      case NORTH:
      case EAST:
      case SOUTH:
      case WEST:
        *state = MOVING;
        break;
    }
  }
}

void Pacman::playerControl()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    *next_dir = NORTH;
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    *next_dir = EAST;
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    *next_dir = SOUTH;
  }

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    *next_dir = WEST;
  }
}

void Pacman::playAnimation(float dt)
{
  if (*state != IDLE)
  {
    *frame_time -= dt;
  }

  if (*frame_time < 0)
  {
    if (*state == DEAD)
    {
      *frame_time = 0.12;
    }
    else
    {
      *frame_time = 0.06;
    }

    *frame_index += 1;
  }

  switch (*state)
  {
    case MOVING:
      animationMoving();
      break;

    case DEAD:
      animationDead();
      break;

    default:
      break;
  }

  setIntRect(textureRects.at(*frame_index));
}

void Pacman::animationMoving()
{
  if (*frame_index > 2)
  {
    *frame_index = 0;
  }

  switch(*current_dir)
  {
    case NORTH:
      setRotation(-90);
      break;

    case EAST:
      setRotation(0);
      break;

    case SOUTH:
      setRotation(90);
      break;

    case WEST:
      setRotation(180);
      break;

    default:
      break;
  }
}

void Pacman::animationDead()
{
  if (4 > *frame_index || *frame_index > 13)
  {
    setRotation(0);
    *frame_index = 4;
  }
}

void Pacman::powerUp()
{
  *is_powered = true;
  *power_timer = 10;
}

bool Pacman::isDeadAnimationDone()
{
  if (*frame_index == 13)
  {
    return true;
  }
  return false;
}

void Pacman::resetPacman()
{
  *current_dir = NONE;
  *next_dir = NONE;
  *next_destination = *spawn_tile;
  *current_destination = *spawn_tile;
  setPosition(spawn_tile->x * 32, spawn_tile->y * 32 + 16);
  setIntRect(textureRects.at(1));
  setRotation(0);

  *frame_time = 0;
  *frame_index = 0;

  *state = IDLE;

  *is_powered = false;
}

void Pacman::setMap1()
{
  *spawn_tile = {14, 26};
  resetPacman();
}

void Pacman::setMap2()
{
 *spawn_tile = {14, 16};
 resetPacman();
}
