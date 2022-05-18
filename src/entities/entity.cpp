#include "entity.hpp"
using namespace Entities;

Entity::Entity(sf::Vector2f position, sf::Vector2f size) {
    this->sprite.setSize(size);
    this->sprite.setPosition(position);
    this->sprite.setOrigin(size / 2.0f);
}

Entity::~Entity() = default;

sf::Vector2f Entity::get_position() const {
    return this->sprite.getPosition();
}

sf::Vector2f Entity::get_size() const {
    return this->sprite.getSize();
}
