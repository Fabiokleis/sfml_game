#include "coin.hpp"
using namespace Entities;

Coin::Coin(int id, double x, double y, double width, double height) : id(id) {
    this->image = new Image("map/coin.png");
    this->image->set_position(sf::Vector2f (x, y));
    this->image->set_size(sf::Vector2f(width, height));
    this->image->set_origin(sf::Vector2f(width / 2.0f, height / 2.0f));
}

sf::RectangleShape Coin::get_sprite() {
    return this->image->get_sprite();
}

Coin::~Coin() {}

int Coin::get_id() const {
    return this->id;
}
