#include "Tile.h"

Tile::Tile(sf::Vector2i tile_pos, int _tile_id, sf::Texture &texture)
{
    tile_id = std::make_unique<int>();

    setPosition(tile_pos.x, tile_pos.y);
    *tile_id = _tile_id;
    setTexture(texture);

    setIntRect(sf::IntRect((*tile_id - 1) * 32, 0, 32, 32));
}
