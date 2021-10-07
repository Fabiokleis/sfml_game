#include "tile.hpp"

Tile::Tile() {}

Tile::Tile(float x, float y, float grid_size_f, sf::Texture* texture) {
    this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
    this->shape.setFillColor(sf::Color::Transparent);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color(0, 255, 0, 100));
    this->shape.setPosition(x, y);
    this->shape.setTexture(texture);
}

Tile::~Tile() {}

void Tile::update() {}

void Tile::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}