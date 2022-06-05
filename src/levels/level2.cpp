#include "level2.hpp"
#include <random>
using namespace Levels;

Level2::Level2() : Level() {

}

Level2::Level2(Managers::GraphicManager *graphic_manager, const std::string &map_name)
        : Level(graphic_manager, map_name) {

}

Level2::~Level2() {

}

void Level2::build_level() {

}

// render order
void Level2::render() {
    this->get_render()->render(this->sprite);
}

void Level2::update() {}
