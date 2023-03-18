#ifndef PACMANSFML_GHOST_H
#define PACMANSFML_GHOST_H

// Standard Library
#include <cmath>

// Game Codebase
#include "../Entity.h"

class Ghost : public Entity
{
 public:
  void updateGhost(float dt);
  void setState(EntityState newState) override;
  void frighten();
  void killGhost();
  virtual void resetGhost();

 protected:
  Ghost(std::shared_ptr<GameData> gameDataPtr);
  virtual void stateChase() = 0;
  virtual void stateScatter();
  virtual void stateDead();
  virtual void stateFright();
  virtual void stateRespawn();
  virtual void stateWaiting();

  void initTextureRects(int y_pos);
  void findBestDirection(sf::Vector2i destination);
  void getRandomDirection();
  void playAnimation(float dt);
  void animationMoving();
  void animationDead();
  void animationFrightened();
  void stateManager(float dt);

  std::unique_ptr<sf::Vector2i> scatter_destination;
  std::unique_ptr<sf::Vector2i> dead_destination;
  std::unique_ptr<sf::Vector2i> respawn_destination;

  std::unique_ptr<float> time_to_release;
  std::unique_ptr<float> spawn_offset;

 private:
  std::unique_ptr<bool> already_frightened;
  std::unique_ptr<bool> on_new_tile;
  std::unique_ptr<float> state_timer;
  std::unique_ptr<int> state_index;

  std::vector<float> state_pattern;
};

#endif // PACMANSFML_GHOST_H
