#include "map.hpp"

Map::Map() {
    this->init_ml();
    this->load_map();
    this->init_variables();
    this->map_objs();
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

sf::Vector2u Map::get_tile_size() {
    return this->tile_size;
}

void Map::map_objs() {

    for (auto layer : this->layers) {
        for (auto obj : layer.objects) {
            if (layer.name == "collision_layer") {
                set_objs(obj);
            }
        }
    }
}

void Map::set_objs(tmx::MapObject obj) {
    this->objs.push_back(obj);
}

tmx::MapObjects Map::get_objs() {
    return this->objs;
}

void Map::update() {}

void Map::render(sf::RenderTarget* target) {
    target->draw(*this->ml);
    this->ml->drawLayer(*target, tmx::MapLayer::Debug);
}