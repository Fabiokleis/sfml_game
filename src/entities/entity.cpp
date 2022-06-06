#include "entity.hpp"
#include "collider.hpp"
using namespace Entities;

Entity::Entity(Managers::GraphicManager *graphic_manager) :
        velocity(0.0f, 0.0f), gravity(9.81f),
        Entie(graphic_manager)
{
    this->sprite = sf::RectangleShape();
}

Entity::Entity() : gravity() {}

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
    this->get_render()->render(this->sprite);
}

void Entity::set_color(sf::Color color) {
    this->sprite.setFillColor(color);
}

void Entity::set_out_color(sf::Color color) {
    this->sprite.setOutlineColor(color);
    this->sprite.setOutlineThickness(2.0f);
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

sf::Vector2f Entity::get_size() const {
    return this->sprite.getSize();
}

void Entity::set_graphic_manager(Managers::GraphicManager *gp){
    this->graphic_manager = gp;
}
