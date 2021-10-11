#include "map.hpp"

Map::Map() {
    this->init_ml();
    this->load_map();
    this->init_variables();
}

Map::~Map() {
    delete ml;
}

void Map::init_ml() {
    std::string path = RESOURCE_PATH;
    this->ml = new tmx::MapLoader(path+"map/");
}

void Map::init_variables() {

    this->tile_size = this->ml->getTileSize();
    this->map_bounds = this-> ml->getMapSize();
    this->layers = this->ml->getLayers();
}

void Map::load_map() {
    ml->load("platform.tmx");
}

sf::Vector2u Map::get_bounds() {
    return this->map_bounds;
}

void Map::map_collision(Player* player) {

    for (auto layer: this->layers) {

        for (auto obj : layer.objects) {
            // verify collision
            if (obj.getPosition().y == player->get_position().y) {
                // set collision state on player
            }
        }
    }
}

void Map::update(Player* player) {
    this->map_collision(player);
}

void Map::render(sf::RenderTarget* target) {
    target->draw(*this->ml);
    // this->ml->drawLayer(*target, tmx::MapLayer::Debug);
}