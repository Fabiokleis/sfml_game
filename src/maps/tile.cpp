#include "tile.hpp"
using namespace Maps;

Tile::Tile(float width, float left, float height, float top) {
    this->body.setSize(sf::Vector2f(width, height));
    this->body.setOrigin(this->body.getSize() / 2.0f);
    this->body.setPosition(left, top);
}

Tile::~Tile() {}

Controllers::Collider Tile::get_collider() {

    return Controllers::Collider(this->body);
}
