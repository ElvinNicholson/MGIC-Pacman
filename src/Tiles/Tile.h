#ifndef PACMANSFML_TILE_H
#define PACMANSFML_TILE_H

// Game Codebase
#include "../GameObject.h"

class Tile : public GameObject
{
public:
    Tile(sf::Vector2i tile_pos, int _tile_id, sf::Texture& texture);
    std::unique_ptr<int> tile_id;

protected:

private:
};


#endif //PACMANSFML_TILE_H
