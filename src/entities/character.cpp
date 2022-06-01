#include <iostream>
#include "entity.hpp"
#include "character.hpp"
using namespace Entities;

Character::Character(Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy, int life_number,
                     sf::Vector2u image_count, float switch_time, States state,
                     const std::string &path_name) :
        Entity(graphic_manager), collide_state(not_colliding), image_count(image_count),
        state(state), last_state(idle), jump_height(0), delta_time(0), switch_time(switch_time), acceleration(0), life_number(life_number)

{
    this->init_texture();
    this->shape = sf::IntRect(cordx, cordy, width, height);
    this->sprite.setTextureRect(shape);
    this->sprite.setTexture(&this->texture);
    this->sprite.setOutlineThickness(1.0f);
    this->sprite.setOutlineColor(sf::Color::Green);
    this->animation = new Managers::Animation(this->texture.getSize(), this->image_count, this->switch_time);
}

Character::Character() : state(), last_state(), jump_height(), delta_time(), switch_time(), acceleration(), life_number(), collide_state(), animation() {}

Character::~Character() {
    delete animation;
}

void Character::init_texture() {
    std::string assets_path = RESOURCE_PATH;
    std::cout << std::endl << assets_path + this->path_name << std::endl;
    if (!this->texture.loadFromFile(assets_path+this->path_name)) {
        std::cout << "ERROR::ENTITIE_TEXTURE:: COULD NOT LOAD TEXTURE FILE." << std::endl;
    }
}

void Character::set_state(const States s) {
    this->state = s;
}

void Character::set_collide_state(CollideStates s) {
    this->collide_state = s;
}

void Character::reset_clock(float dt) {
    this->delta_time = dt;
}

int Character::get_life_number() const {
    return this->life_number;
}

Managers::Animation& Character::get_animation() {
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
