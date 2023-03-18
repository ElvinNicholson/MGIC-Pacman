#include "Title.h"

Title::Title(std::shared_ptr<States> _gamestate, std::shared_ptr<int> _selected_map) : Gamestate(_gamestate), selected_map(_selected_map)
{
  mouse_pos = std::make_unique<sf::Vector2i>();

  logo_texture = std::make_unique<sf::Texture>();
  logo_texture->loadFromFile("../Data/Images/pacman_logo.png");

  logo = std::make_unique<GameObject>();
  logo->setTexture(*logo_texture);
  logo->setPosition(448 - logo->getGlobalBounds().width/2, 300);

  map1_button = std::make_unique<Button>("../Data/Images/map1_button.png");
  map1_button->setIntRect(sf::IntRect(0, 0, 248, 152));
  map1_button->setPosition(274 - map1_button->getGlobalBounds().width/2, 550);

  map2_button = std::make_unique<Button>("../Data/Images/map2_button.png");
  map2_button->setIntRect(sf::IntRect(0, 0, 248, 152));
  map2_button->setPosition(622 - map2_button->getGlobalBounds().width/2, 550);

}

void Title::update(float dt)
{

}

void Title::render(sf::RenderWindow& window)
{
  *mouse_pos = sf::Mouse::getPosition(window);

  logo->renderObject(window);
  map1_button->renderObject(window);
  map2_button->renderObject(window);
}

void Title::eventHandler(sf::Event event)
{
  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button ==  sf::Mouse::Left)
  {
    if (map1_button->mouseCollision(*mouse_pos))
    {
      map1_button->setIntRect(sf::IntRect(248, 0, 248, 152));
    }

    if (map2_button->mouseCollision(*mouse_pos))
    {
      map2_button->setIntRect(sf::IntRect(248, 0, 248, 152));
    }
  }
  else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
  {
    if (map1_button->mouseCollision(*mouse_pos))
    {
      map1_button->setIntRect(sf::IntRect(0, 0, 248, 152));
      *selected_map = 1;
      *gamestate = GAMEPLAY;
    }

    if (map2_button->mouseCollision(*mouse_pos))
    {
      map2_button->setIntRect(sf::IntRect(0, 0, 248, 152));
      *selected_map = 2;
      *gamestate = GAMEPLAY;
    }
  }
}
