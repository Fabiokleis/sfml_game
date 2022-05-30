#include "tiles.hpp"
using namespace Maps;

Tiles::Tiles(rapidjson::Value &value) {
    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            tiles_array.emplace_back(obj);
        }
    }
    for (auto &tile : this->tiles_array) {
        tile.set_position(tile.get_x() + tile.get_width() / 2.0f, tile.get_y() + tile.get_height() / 2.0f);
        tile.set_size(tile.get_width(), tile.get_height());
        tile.set_origin(tile.get_width() / 2.0f, tile.get_height() / 2.0f);
        tile.set_color(sf::Color::Transparent);
        tile.set_thickness(1.0f);
        tile.set_outline_color(sf::Color::Green);
    }
}

Tiles::Tiles() : tiles_array() {}

Tiles::~Tiles() {}

std::vector<Object> Tiles::get_tiles() {
    return this->tiles_array;
}

std::vector<Entities::Coin> Tiles::get_coins() {

    for (auto &tile : this->tiles_array) {

        if (tile.get_type() == "coin") {

            this->coins.emplace_back(Entities::Coin(COIN_PATH, tile.get_id(), tile.get_x(), tile.get_y(), tile.get_width(), tile.get_height()));
        }
    }
    return this->coins;
}