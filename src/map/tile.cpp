#include <iostream>
#include "tile.hpp"
using namespace std;

Tile::Tile(float width, float left, float height, float top) {
    this->body.setSize(sf::Vector2f(width, height));
    this->body.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    this->body.setPosition(sf::Vector2f(left, top));
}

sf::Vector2f Tile::get_position() {
    return this->body.getPosition();
}

sf::Vector2f Tile::get_half_size() {
    return this->body.getSize() / 2.0f;
}

void Tile::set_hitbox(float width, float left, float height, float top) {
    this->body.setSize(sf::Vector2f(width, height));
    this->body.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    this->body.setPosition(sf::Vector2f(left, top));
}

sf::RectangleShape Tile::get_body() {
    return this->body;
}

bool Tile::check_collision(sf::RectangleShape body) {
}

void Tile::move(float dx, float dy) {
    this->body.move(dx, dy);
}

Tile::~Tile() {}