#ifndef PACMANSFML_COLLECTIBLE_H
#define PACMANSFML_COLLECTIBLE_H

// Game Codebase
#include "../GameObject.h"
#include "CollectibleType.h"

class Collectible : public GameObject
{
 public:
  Collectible(std::unique_ptr<sf::Texture>& texture, CollectibleType type_);

  std::unique_ptr<CollectibleType> type;
  std::unique_ptr<int> points;

 protected:

 private:

};

#endif // PACMANSFML_COLLECTIBLE_H
