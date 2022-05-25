#include "platforms.hpp"
using namespace Maps;

Platforms::Platforms(std::vector<Object> platforms_array) : platforms_array(platforms_array) {}

Platforms::Platforms() : platforms_array() {}

std::vector<Object> Platforms::get_platforms() {
    return this->platforms_array;
}

Platforms::~Platforms() = default;