#include "characters/zezinho.h"

using namespace Entities::Characters;

Zezinho::Zezinho() {

}

Zezinho::Zezinho(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                int life_number, sf::Vector2u image_count, float switch_time, States state,
                const std::string &path_name, float *delta_time):
                Enemy(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time),
                id(id)
{
    this->acceleration = 100.0f;
    this->velocity = sf::Vector2f(0,0);
    this->type = "zezinho";
}

Zezinho::~Zezinho() {

}

std::string Zezinho::get_type() {
    return this->type;
}

int Zezinho::get_id() const {
    return this->id;
}

void Zezinho::update_animation() {
    if (state == walking_right) {
        this->get_animation().update(0, (*this->delta_time), true);
    } else {
        this->get_animation().update(0, (*this->delta_time), false);
    }
    this->sprite.setTextureRect(this->get_animation().rect);
}

void Zezinho::move(float dir_x, float dir_y) {
    this->velocity.x += dir_x * this->acceleration;
}

void Zezinho::update() {
    //this->update_physics();
    this->update_animation();
    this->update_move();
    if(velocity.x < 0){
        this->state = walking_left;
    }else if(velocity.x > 0){
        this->state = walking_right;
    }
    if(velocity.x == 0){
        this->state = idle;
    }
}

void Zezinho::update_move() {

}
