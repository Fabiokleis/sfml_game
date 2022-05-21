#include "tile.hpp"
using namespace Maps;

Tile::Tile(float width, float left, float height, float top) {
    this->body.setSize(sf::Vector2f(width, height));
    this->body.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    this->body.setPosition(left, top);
    this->body.setOutlineThickness(1.0f);
    this->body.setOutlineColor(sf::Color::Magenta);
    this->body.setFillColor(sf::Color::Transparent);

}

Tile::~Tile() {}

Controllers::Collider Tile::get_collider() {
    return Controllers::Collider{this->body};
}

sf::RectangleShape Tile::get_body() {
    return this->body;
}
