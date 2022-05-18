#include <iostream>
#include <string>
#include <utility>
#include "character.hpp"
#include "collider.hpp"
#include "config.h"
using namespace Entities;

Character::Character(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord, std::string name) :
    Entity(position, size)
{
    this->velocity = velocity;
    this->path_name = std::move(name);
    this->state = falling;
    this->shape = sf::IntRect(static_cast<int>(cord.x), static_cast<int>(cord.y), static_cast<int>(size.x), static_cast<int>(size.y));
    init_texture();
    this->sprite.setTextureRect(shape);
    this->sprite.setTexture(&this->texture);
}

Character::~Character() {}

void Character::init_texture() {
    std::string assets_path = RESOURCE_PATH;
    std::cout << std::endl << assets_path + this->path_name << std::endl;
    if (!this->texture.loadFromFile(assets_path+this->path_name)) {
        std::cout << "ERROR::CHARACTER_TEXTURE:: COULD NOT LOAD TEXTURE FILE." << std::endl;
    }
}

sf::Vector2f& Character::get_velocity() {
    return this->velocity;
}

Controllers::Collider Character::get_collider() {
    return Controllers::Collider{this->sprite};
}

void Character::set_state(const State s) {
    this->state = s;
}