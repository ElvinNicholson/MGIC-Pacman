#ifndef PACMANSFML_GAMESTATE_H
#define PACMANSFML_GAMESTATE_H

// Standard Library
#include <memory>

// External Library
#include <SFML/Graphics.hpp>

// Game Codebase
#include "States.h"


class Gamestate
{
 public:
  Gamestate(std::shared_ptr<States> _gamestate);

  virtual void update(float dt) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
  virtual void eventHandler(sf::Event event) = 0;

 protected:
  std::shared_ptr<States> gamestate;

 private:

};

#endif // PACMANSFML_GAMESTATE_H
