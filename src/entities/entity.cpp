#include "entity.hpp"
#include "collider.hpp"
using namespace Entities;

Entity::Entity(Managers::GraphicManager &graphicManager) :
        velocity(0.0f, 0.0f), gravity(9.81f),
        Entie(graphicManager)
{
    this->sprite = sf::RectangleShape();
}

Entity::~Entity() {}

sf::RectangleShape Entity::get_sprite() const {
    return this->sprite;
}

sf::Vector2f Entity::get_position() const {
    return this->sprite.getPosition();
}

sf::Vector2f& Entity::get_velocity() {
    return this->velocity;
}

Managers::Collider Entity::get_collider() {
    return Managers::Collider{this->sprite};
}

void Entity::render() {
    this->get_render().render(this->sprite);
}

void Entity::set_position(double x, double y) {
    this->sprite.setPosition(x, y);
}

void Entity::set_size(double width, double height) {
    this->sprite.setSize(sf::Vector2f(width, height));
}

void Entity::set_velocity(float x, float y) {
    this->velocity.x = x;
    this->velocity.y = y;
}

void Entity::set_origin(double x, double y) {
    this->sprite.setOrigin(x, y);
}
