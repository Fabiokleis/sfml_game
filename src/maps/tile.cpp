#include "tile.hpp"
#include <utility>
using namespace Maps;

Tile::Tile(std::string type, float width, float left, float height, float top) {
    this->type = std::move(type);
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

std::string Tile::get_type() {
    return this->type;
}
