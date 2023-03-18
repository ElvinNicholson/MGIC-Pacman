#ifndef PACMANSFML_TITLE_H
#define PACMANSFML_TITLE_H

// Game Codebase
#include "Gamestate.h"
#include "../GameObject.h"
#include "../GameObject/Button.h"

class Title : public Gamestate
{
 public:
  Title(std::shared_ptr<States> _gamestate, std::shared_ptr<int> _selected_map);

  void update(float dt) override;
  void render(sf::RenderWindow &window) override;
  void eventHandler(sf::Event event) override;

 protected:

 private:
  std::shared_ptr<int> selected_map;

  std::unique_ptr<sf::Vector2i> mouse_pos;

  std::unique_ptr<sf::Texture> logo_texture;
  std::unique_ptr<GameObject> logo;

  std::unique_ptr<Button> map1_button;
  std::unique_ptr<Button> map2_button;
};

#endif // PACMANSFML_TITLE_H
