#ifndef PACMANSFML_BUTTON_H
#define PACMANSFML_BUTTON_H

// Game Codebase
#include "../GameObject.h"

class Button : public GameObject
{
 public:
  Button(std::string filepath);
  bool mouseCollision(sf::Vector2i mouse_pos);

 protected:

 private:
  std::unique_ptr<sf::Texture> texture;
};

#endif // PACMANSFML_BUTTON_H
