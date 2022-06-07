#include "characters/dunga.hpp"

using namespace Entities::Characters;

Dunga::Dunga(){

}

Dunga::Dunga(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
             int life_number, sf::Vector2u image_count, float switch_time, States state,
             const std::string &path_name, float *delta_time):
            Enemy(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time),
            id(id)
{
    this->acceleration = 100.0f;
    this->velocity = sf::Vector2f(0,0);
    this->type = "dunga";
    this->state = idle;
}

Dunga::~Dunga(){

}

std::string Dunga::get_type() {
    return this->type;
}

int Dunga::get_id() const{
    return this->id;
}

void Dunga::update_animation() {
    this->get_animation().update(0, (*this->delta_time), false);
    this->sprite.setTextureRect(this->get_animation().rect);
}

void Dunga::move(float dir_x, float dir_y) {
    // accelerate
//    this->velocity.x += dir_x * this->acceleration;
}

void Dunga::update() {
    this->update_move();
    this->update_physics();
    this->update_animation();
}

void Enemy::update_animation() {
    this->sprite.setTextureRect(this->get_animation().rect);
}

void Dunga::update_move() {
    if(velocity.x == -1.0f){
        this->state = walking_left;
    }else if(velocity.x == 1.0f){
        this->state = walking_right;
    } else if(velocity.x == 0){
        this->state = idle;
    }
}
