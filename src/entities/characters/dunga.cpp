#include "characters/dunga.hpp"

using namespace Entities::Characters;

Dunga::Dunga(){

}

Dunga::Dunga(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
             int life_number, sf::Vector2u image_count, float switch_time, States state,
             const std::string &path_name, float *delta_time):
            Enemy(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time)
{
    this->acceleration = 100.0f;
    this->velocity = sf::Vector2f(0,0);
    this->type = "dunga";
    this->state = idle;
    this->id = id;
    this->moveMax = 160;
}

Dunga::~Dunga(){

}

void Dunga::update_animation() {
    this->get_animation().update(0, (*this->delta_time), false);
    this->sprite.setTextureRect(this->get_animation().rect);
}

void Dunga::move(float dir_x, float dir_y) {
    // accelerate
    this->velocity.x += dir_x * this->acceleration;
}

void Dunga::update() {
    this->update_move();
    this->update_physics();
    this->update_animation();
}

void Dunga::update_move() {
    if(state == 1){
        this->move(0.01f, 0.0f);
        if(moveTimer >= moveMax) {
            state = walking_left;
            moveTimer = 0;
            velocity.x = 0;
        }
    } else{
        this->move(-0.01f, 0.0f);
        if(moveTimer >= moveMax){
            state = walking_right;
            moveTimer = 0;
            velocity.x = 0;
        }
    }
    moveTimer++;
}
