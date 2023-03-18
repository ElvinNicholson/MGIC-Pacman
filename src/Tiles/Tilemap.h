#ifndef PACMANSFML_TILEMAP_H
#define PACMANSFML_TILEMAP_H

// External Library
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

// Game Codebase
#include "Tile.h"

class Tilemap
{
public:
    Tilemap(std::string file_location);
    std::vector<std::unique_ptr<Tile>>& getTilemap();
    std::vector<int>& getCollectibleMap();

protected:

private:
    std::vector<std::unique_ptr<Tile>> vector_tile;
    std::vector<int> collectible_map;
    std::unique_ptr<sf::Texture> map_texture;

};


#endif //PACMANSFML_TILEMAP_H
