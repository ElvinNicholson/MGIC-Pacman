#ifndef PACMANSFML_PACMAN_H
#define PACMANSFML_PACMAN_H

// Game Codebase
#include "Entity.h"

class Pacman : public Entity
{
 public:
  Pacman(std::unique_ptr<sf::Texture> &texture, std::shared_ptr<GameData> gameDataPtr);

  void updatePacman(float dt);
  void powerUp();
  bool isDeadAnimationDone();
  void resetPacman();
  void setMap1() override;
  void setMap2() override;

 protected:

 private:
  void changeState(float dt);
  void playerControl();
  void playAnimation(float dt);
  void animationMoving();
  void animationDead();

  std::unique_ptr<bool> is_powered;
  std::unique_ptr<float> power_timer;
};

#endif // PACMANSFML_PACMAN_H
