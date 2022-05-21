#include "entity.hpp"
using namespace Entities;

Entity::Entity(sf::Vector2f position, sf::Vector2f size) {
    this->sprite.setSize(size);
    this->sprite.setPosition(position);
    this->sprite.setOrigin(size / 2.0f);
    this->life = true;
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

const sf::Vector2f Entity::get_position() const {
    return this->sprite.getPosition();
}

void Entity::set_life(bool flag) {
    this->life = flag;
}

bool Entity::get_life() {
    return this->life;
}

Entity::Entity() = default;
Entity::~Entity() = default;

