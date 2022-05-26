#include "tiles.hpp"
using namespace Maps;

Tiles::Tiles(rapidjson::Value &value) {
    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            tiles_array.emplace_back(obj);

            if (std::string(obj["type"].GetString()) == "rect") {
                this->tiles_rect_array.emplace_back(obj);
            } else if (std::string(obj["type"].GetString()) == "triangle") {
                this->tiles_triangle_array.emplace_back(obj);
            }

        }
    }
    for (auto &tile : this->tiles_array) {
        if (tile.get_type() == "triangle") {
            tile.set_point(0, tile.get_polys()[0], tile.get_polys()[1]);
            tile.set_point(1, tile.get_polys()[2], tile.get_polys()[3]);
            tile.set_point(2, tile.get_polys()[4], tile.get_polys()[5]);

            tile.set_position(tile.get_x(), tile.get_y());
            tile.get_triangle_sprite().setFillColor(sf::Color::White);
            
            tile.set_thickness(1.0f);
            tile.set_outline_color(sf::Color::Green);
        } else if (tile.get_type() == "rect") {
            tile.set_position(tile.get_x() + tile.get_width() / 2.0f, tile.get_y() + tile.get_height() / 2.0f);
            tile.set_size(tile.get_width(), tile.get_height());
            tile.set_origin(tile.get_width() / 2.0f, tile.get_height() / 2.0f);
            tile.set_color(sf::Color::Transparent);
            tile.set_thickness(1.0f);
            tile.set_outline_color(sf::Color::Green);
        }
    }
}

std::vector<Object> Tiles::get_tiles() {
    return this->tiles_array;
}

Tiles::Tiles() : tiles_array() {}

Tiles::~Tiles() = default;
