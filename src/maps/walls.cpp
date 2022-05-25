#include "walls.hpp"
using namespace Maps;

Walls::Walls(std::vector<Object> walls_array) : walls_array(walls_array) {}

Walls::Walls() : walls_array() {}

std::vector<Object> Walls::get_walls() {
    return this->walls_array;
}

Walls::~Walls() = default;
