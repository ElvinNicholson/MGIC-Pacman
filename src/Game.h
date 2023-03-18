
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

// External Library
#include <SFML/Graphics.hpp>

// Game Codebase
#include "Gamestate/Gameplay.h"
#include "Gamestate/Title.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  bool isStateChanged();

  bool is_map_loaded;

  sf::RenderWindow& window;

  std::unique_ptr<Title> title;
  std::unique_ptr<Gameplay> gameplay;
  std::shared_ptr<States> gamestate;
  std::unique_ptr<States> last_state;

  std::shared_ptr<int> selected_map;
};

#endif // PLATFORMER_GAME_H
