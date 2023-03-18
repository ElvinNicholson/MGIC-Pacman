#ifndef PACMANSFML_GAMEOBJECT_H
#define PACMANSFML_GAMEOBJECT_H

// Standard Library
#include <memory>
#include <iostream>
#include <cmath>

// External Library
#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();

  void setTexture(sf::Texture &texture);
  void setIntRect(sf::IntRect intRect);
  void setPosition(float x, float y);
  void move(float x, float y);
  void renderObject(sf::RenderWindow& renderWindow);
  void setOriginCentre();
  void setScale(float x, float y);
  void setRotation(float angle);
  sf::Vector2f getPosition();
  sf::Vector2i getTilePos();
  sf::FloatRect getGlobalBounds();

 protected:
  std::unique_ptr<sf::Sprite> sprite;

 private:
};

#endif // PACMANSFML_GAMEOBJECT_H
