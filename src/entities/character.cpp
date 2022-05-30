#include <iostream>
#include <string>
#include <utility>
#include "character.hpp"
#include "collider.hpp"
#include "config.h"
using namespace Entities;

Character::Character(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord, sf::Vector2u image_count, float switch_time, States state, std::string path_name) :
        velocity(velocity), path_name(path_name), image_count(image_count), switch_time(switch_time), state(state), collide_state(), last_state(state),
        Entity(position, size)
{
    this->shape = sf::IntRect(static_cast<int>(cord.x), static_cast<int>(cord.y), static_cast<int>(size.x), static_cast<int>(size.y));
    init_texture();
    this->sprite.setTextureRect(shape);
    this->sprite.setTexture(&this->texture);
    this->animation = new Controllers::Animation(this->texture.getSize(), this->image_count, this->switch_time);

}

Character::Character() : velocity(), path_name(), image_count(), switch_time(), state(idle), collide_state(), last_state(idle), animation() {};

Character::~Character() {
    delete animation;
}

void Character::init_texture() {
    std::string assets_path = RESOURCE_PATH;
    std::cout << std::endl << assets_path + this->path_name << std::endl;
    if (!this->texture.loadFromFile(assets_path+this->path_name)) {
        std::cout << "ERROR::CHARACTER_TEXTURE:: COULD NOT LOAD TEXTURE FILE." << std::endl;
    }
}

void Character::set_state(const States s) {
    this->state = s;
}

void Character::set_collide_state(CollideStates s) {
    this->collide_state = s;
}

void Character::set_rect(sf::IntRect rect) {
    this->sprite.setTextureRect(rect);
}

sf::Vector2f& Character::get_velocity() {
    return this->velocity;
}

Controllers::Collider Character::get_collider() {
    return Controllers::Collider{this->sprite};
}

Controllers::Animation& Character::get_animation() {
    return *this->animation;
}

CollideStates Character::get_collide_state() {
    return this->collide_state;
}

void Character::set_last_state(States s) {
    this->last_state = s;
}

States Character::get_state() {
    return this->state;
}
