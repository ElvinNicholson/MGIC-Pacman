#include "Tilemap.h"

Tilemap::Tilemap(std::string file_location)
{
    map_texture = std::make_unique<sf::Texture>();
    map_texture->loadFromFile("../Data/Images/MazeTilemap.png");

    tmx::Map map;
    map.load(file_location);

    std::vector<tmx::TileLayer::Tile> map_tiles;
    map_tiles = map.getLayers()[0]->getLayerAs<tmx::TileLayer>().getTiles();

    int map_width = map.getTileCount().x;
    int map_height = map.getTileCount().y;

    vector_tile.reserve(map_width * map_height);

    int idx;
    int idy;
    int index = 0;

    for (auto& tile : map_tiles)
    {
        idx = index / map_width;
        idy = index % map_width;

        vector_tile.emplace_back(std::make_unique<Tile>(sf::Vector2i(idy * 32, idx * 32), tile.ID, *map_texture));
        index++;
    }

    std::vector<tmx::TileLayer::Tile> map_collectible;
    map_collectible = map.getLayers()[1]->getLayerAs<tmx::TileLayer>().getTiles();

    collectible_map.reserve(map_width * map_height);

    for (auto& collectible : map_collectible)
    {
        collectible_map.emplace_back(collectible.ID);
    }
}


std::vector<std::unique_ptr<Tile>> &Tilemap::getTilemap()
{
    return vector_tile;
}

std::vector<int> &Tilemap::getCollectibleMap()
{
    return collectible_map;
}
