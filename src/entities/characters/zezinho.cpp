#include "characters/zezinho.h"

using namespace Entities::Characters;

Zezinho::Zezinho() {

}

Zezinho::Zezinho(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                int life_number, sf::Vector2u image_count, float switch_time, States state,
                const std::string &path_name, float *delta_time, Player* player):
                Enemy(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time),
                p1(player), visible(true),timer(0)
{
    this->acceleration = 150.0f;
    this->velocity = sf::Vector2f(0,0);
    this->jump_height = 10.0f;
    this->state = idle;
    this->type = "zezinho";
    this->id = id;
    this->moveMax = 190;
    this->moveTimer = 0;
}

Zezinho::~Zezinho() {

}

void Zezinho::update_animation() {
    if(visible){
        if (state == walking_right) {
            this->get_animation().update(0, (*this->delta_time), true);
        } else {
            this->get_animation().update(0, (*this->delta_time), false);
        }
        this->sprite.setTextureRect(this->get_animation().rect);
    }
}

void Zezinho::move(float dir_x, float dir_y) {
    this->velocity.x += dir_x * this->acceleration;
}

void Zezinho::update() {
    this->update_physics();
    this->update_move();
    this->update_visible();
    this->update_animation();
}

void Zezinho::update_move() {
    float vel = 0;
    int timer = 0;
    if(abs(get_position().x - p1->get_position().x) <= 350){
        vel = 0.04;
        timer = 2;
    } else {
        vel = 0.01;
        timer = 1;
    }
    if(state == 1){
        this->move(vel, 0.0f);
        if(moveTimer >= moveMax) {
            state = walking_left;
            moveTimer = 0;
            this->velocity.x = 0;
        }
    } else{
        this->move(-vel, 0.0f);
        if(moveTimer >= moveMax){
            state = walking_right;
            moveTimer = 0;
            this->velocity.x = 0;
        }
    }
    moveTimer += timer;
}

void Zezinho::set_player(Player* player) {
    this->p1 = player;
}

void Zezinho::update_visible() {
    timer++;
    if(timer >= 345){
        this->visible = false;
        this->get_animation().update(1, (*this->delta_time), false);
        //this->set_out_color(sf::Color::Transparent);
        this->sprite.setTextureRect(this->get_animation().rect);
        timer = -300;
    } else if(timer > 0 && !visible){
        this->visible = true;
        this->set_out_color(sf::Color::Green);
    }
}
