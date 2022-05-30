#include "entity.hpp"
using namespace Entities;

Entity::Entity(double x, double y, double width, double height) {
    this->sprite.setSize(sf::Vector2f(width, height));
    this->sprite.setPosition(x, y);
    this->sprite.setOrigin(width / 2.0f, height / 2.0f);
}

Entity::Entity() {}
Entity::~Entity() {}

sf::RectangleShape Entity::get_sprite() const {
    return this->sprite;
}

sf::Vector2f Entity::get_position() const {
    return this->sprite.getPosition();
}

void Entity::set_position(double x, double y) {
    this->sprite.setPosition(x, y);
}
void Entity::set_size(double width, double height) {
    this->sprite.setSize(sf::Vector2f(width, height));
}

void Entity::set_origin(double x, double y) {
    this->sprite.setOrigin(x, y);
}

void Entity::set_color(sf::Color color) {
    this->sprite.setFillColor(color);
}

void Entity::set_thickness(float thick) {
    this->sprite.setOutlineThickness(thick);
}
void Entity::set_outline_color(sf::Color color) {
    this->sprite.setOutlineColor(color);
}

void Entity::set_texture(sf::Texture *texture) {
    this->sprite.setTexture(texture);
}
