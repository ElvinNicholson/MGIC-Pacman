#include "Collectible.h"

Collectible::Collectible(std::unique_ptr<sf::Texture>& texture, CollectibleType type_)
{
  type = std::make_unique<CollectibleType>();
  points = std::make_unique<int>();

  *type = type_;
  setTexture(*texture);

  switch (*type)
  {
    case NORMAL_PELLET:
      setIntRect(sf::IntRect(64, 64, 32, 32));
      *points = 10;
      break;

    case POWER_PELLET:
      setIntRect(sf::IntRect(128, 64, 32, 32));
      *points = 0;
      break;

    case CHERRY:
      setIntRect(sf::IntRect(64, 96, 32, 32));
      *points = 100;
      break;

    case ORANGE:
      setIntRect(sf::IntRect(128, 96, 32, 32));
      *points = 500;
      break;

    case MELON:
      setIntRect(sf::IntRect(192, 96, 32, 32));
      *points = 1000;

    default:
      break;
  }

  setScale(2, 2);
  setOriginCentre();
}
