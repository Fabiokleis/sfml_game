#include "entity.hpp"
using namespace Entities;

Entity::Entity(sf::Vector2f position, sf::Vector2f size) {
    this->sprite.setSize(size);
    this->sprite.setPosition(position);
    this->sprite.setOrigin(size / 2.0f);
}

sf::RectangleShape Entity::get_sprite() const {
    return this->sprite;
}

void Entity::set_position(sf::Vector2f position) {
    this->sprite.setPosition(position);
}

void Entity::set_size(sf::Vector2f size) {
    this->sprite.setSize(size);
}

sf::Vector2f Entity::get_position() const {
    return this->sprite.getPosition();
}

void Entity::set_origin(sf::Vector2f origin) {
    this->sprite.setOrigin(origin);
}

Entity::Entity() = default;
Entity::~Entity() = default;

