#ifndef PACMANSFML_GAMEPLAY_H
#define PACMANSFML_GAMEPLAY_H

// Standard Library
#include <fstream>
#include <memory>

// Game Codebase
#include "Gamestate.h"
#include "../GameData.h"
#include "../Entity/Pacman.h"
#include "../Entity/Ghost/Blinky.h"
#include "../Entity/Ghost/Pinky.h"
#include "../Entity/Ghost/Inky.h"
#include "../Entity/Ghost/Clyde.h"
#include "../Collectible/Collectible.h"
#include "../src/Audio/AudioManager.h"

class Gameplay : public Gamestate
{
 public:
  Gameplay(std::shared_ptr<States> _gamestate);

  void update(float dt) override;
  void render(sf::RenderWindow &window) override;
  void eventHandler(sf::Event event) override;
  void setMap1();
  void setMap2();

 protected:

 private:
  void initAllText();
  void placeCollectibles();
  void resetGame();
  void resetLevel();

  void entityManager(float dt);
  void collectibleManager();
  bool pauseManager(float dt);
  void pauseGame(float pause_time);

  void updateScore(int points);
  void updateHighScore();
  void updateLivesCounter();

  bool isGhostOnState(EntityState state);
  bool pointCollision(sf::Vector2f point, sf::FloatRect object);

  void killPacman();
  void checkLives();
  void checkPellets();
  void setMidText(std::string string, sf::Color color = sf::Color(0, 0, 0));
  void placeFruit();

  void readHighScore();
  void writeHighScore();

  std::unique_ptr<bool> pause;
  std::unique_ptr<bool> is_game_started;
  std::unique_ptr<bool> is_pacman_dying;
  std::unique_ptr<float> pause_timer;
  std::unique_ptr<int> current_score;
  std::unique_ptr<int> high_score;
  std::unique_ptr<int> lives;
  std::unique_ptr<int> map;
  std::unique_ptr<int> ghost_eaten;

  std::unique_ptr<sf::Font> font;
  std::unique_ptr<sf::Text> current_score_text;
  std::unique_ptr<sf::Text> current_score_number;
  std::unique_ptr<sf::Text> high_score_text;
  std::unique_ptr<sf::Text> high_score_number;
  std::unique_ptr<sf::Text> middle_text;

  std::unique_ptr<sf::Texture> entityTexture;
  std::unique_ptr<Pacman> pacman;
  std::vector<std::unique_ptr<Ghost>> ghosts;

  std::unique_ptr<GameObject> lives_counter;

  std::vector<Collectible> collectibles;

  std::shared_ptr<GameData> gameData;
  std::unique_ptr<AudioManager> audioManager;
};

#endif // PACMANSFML_GAMEPLAY_H
