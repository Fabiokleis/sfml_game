#include "platforms.hpp"
using namespace Maps;

Platforms::Platforms(std::vector<Object> platforms_array) : platforms_array(platforms_array) {
    for (auto &plat : this->platforms_array) {
        plat.set_position(plat.get_x() + plat.get_width() / 2.0f, plat.get_y() + plat.get_height() / 2.0f);
        plat.set_size(plat.get_width(), plat.get_height());
        plat.set_origin(plat.get_width() / 2.0f, plat.get_height() / 2.0f);
        plat.set_color(sf::Color::Transparent);
        plat.set_thickness(1.0f);
        plat.set_outline_color(sf::Color::Magenta);
    }
}

Platforms::Platforms() : platforms_array() {}

std::vector<Object> Platforms::get_platforms() {
    return this->platforms_array;
}

Platforms::~Platforms() = default;