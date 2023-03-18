#include "Button.h"
Button::Button(std::string filepath)
{
  texture = std::make_unique<sf::Texture>();
  texture->loadFromFile(filepath);

  setTexture(*texture);
}

bool Button::mouseCollision(sf::Vector2i mouse_pos)
{
  sf::Vector2f sprite_max = {getGlobalBounds().left + getGlobalBounds().width, getGlobalBounds().top + getGlobalBounds().height};

  if (
    mouse_pos.x < sprite_max.x &&
    mouse_pos.x > getGlobalBounds().left &&
    mouse_pos.y < sprite_max.y &&
    mouse_pos.y > getGlobalBounds().top
    )
  {
    return true;
  }
  return false;
}
