#ifndef PACMANSFML_ENTITY_H
#define PACMANSFML_ENTITY_H

// Game codebase
#include "../GameObject.h"
#include "../GameData.h"
#include "Direction.h"
#include "EntityState.h"

class Entity : public GameObject
{
 public:
  Entity(std::shared_ptr<GameData> gameDataPtr);

  void moveEntity(float dt);
  virtual void setState(EntityState newState);
  EntityState getState();
  Direction getDirection();
  virtual void setMap1() = 0;
  virtual void setMap2() = 0;

 protected:
  bool checkWallCollision(sf::Vector2i tilePos);
  void findAdjacentTiles(Direction direction, sf::Vector2i& destination);
  void portal();

  std::unique_ptr<Direction> current_dir;
  std::unique_ptr<Direction> next_dir;
  std::unique_ptr<sf::Vector2i> current_destination;
  std::unique_ptr<sf::Vector2i> next_destination;
  std::unique_ptr<sf::Vector2i> spawn_tile;

  std::unique_ptr<EntityState> state;

  std::vector<sf::IntRect> textureRects;

  std::unique_ptr<float> speed;
  std::unique_ptr<float> frame_time;
  std::unique_ptr<int> frame_index;

  std::shared_ptr<GameData> gameData;
 private:
};

#endif // PACMANSFML_ENTITY_H
