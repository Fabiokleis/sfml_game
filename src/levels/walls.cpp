#include "walls.hpp"
using namespace Levels;

Walls::Walls(rapidjson::Value &value) {
    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            this->walls_array.emplace_back(obj);
        }
    }
    for (auto &wall : this->walls_array) {
        wall.set_position(wall.get_x() + wall.get_width() / 2.0f, wall.get_y() + wall.get_height() / 2.0f);
        wall.set_size(wall.get_width(), wall.get_height());
        wall.set_origin(wall.get_width() / 2.0f, wall.get_height() / 2.0f);
        wall.set_color(sf::Color::Transparent);
        wall.set_thickness(1.0f);
        wall.set_outline_color(sf::Color::Cyan);
    }
}

Walls::Walls() : walls_array() {}

std::vector<Object> Walls::get_walls() {
    return this->walls_array;
}

Walls::~Walls() {}
