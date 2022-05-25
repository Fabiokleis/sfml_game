#include "tiles.hpp"
using namespace Maps;

Tiles::Tiles(std::vector<Object> tiles_array) : tiles_array(tiles_array) {}

std::vector<Object> Tiles::get_tiles() {
    return this->tiles_array;
}

Tiles::Tiles() : tiles_array() {}

Tiles::~Tiles() = default;
