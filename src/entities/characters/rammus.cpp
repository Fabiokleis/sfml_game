#include "characters/rammus.h"
using namespace Entities::Characters;

Rammus::Rammus() {}

Rammus::Rammus(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
               int life_number, sf::Vector2u image_count, float switch_time, States state,
               const std::string &path_name, float *delta_time):
        Enemy(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time),
        cdr(150)
{
    this->state = idle;
    this->acceleration = 150.0f;
    this->velocity = sf::Vector2f(0,0);
    this->type = "rammus";
    this->attackTimer = 0;
    this->moveMax = 170;
    this->canAttack = 0;
    this->fireB = new FireBall(graphic_manager, delta_time);
    this->id = id;
}

Rammus::~Rammus() {

}

void Rammus::update_animation() {
    if (canAttack) {
        if (state == walking_right) {
            this->get_animation().update(0, (*this->delta_time), false);
        } else {
            this->get_animation().update(0, (*this->delta_time), true);
        }
    } else {
        if (state == walking_right) {
            this->get_animation().update(1, (*this->delta_time), false);
        } else {
            this->get_animation().update(1, (*this->delta_time), true);
        }
    }
    this->sprite.setTextureRect(this->get_animation().rect);
}

void Rammus::update_move() {
    if(state == walking_right){
        this->move(0.01f, 0.0f);
        if(moveTimer >= moveMax) {
            state = walking_left;
            moveTimer = 0;
            this->velocity.x = 0;
        }
    } else{
        this->move(-0.01f, 0.0f);
        if(moveTimer >= moveMax){
            state = walking_right;
            moveTimer = 0;
            this->velocity.x = 0;
        }
    }
    moveTimer++;
}

void Rammus::move(float dir_x, float dir_y) {
    this->velocity.x += dir_x * this->acceleration;
}

void Rammus::update_attack() {
    if(attackTimer >= cdr && !canAttack){
        canAttack = true;
        this->attack();
        attackTimer = -cdr;
    } else if (attackTimer > 0){
        canAttack = false;
    }
    attackTimer++;
}

void Rammus::attack() {
    if(abs(get_position().x - p1->get_position().x) <= 500){
        if (get_position().x - p1->get_position().x >= 0) {
            state = walking_left;
            fireB->shoot(this->get_position(), sf::Vector2f(-200, 0));
        } else {
            state = walking_right;
            fireB->shoot(this->get_position(), sf::Vector2f(200, 0));
        }
    }
}

void Rammus::update() {
    this->update_physics();
    this->update_animation();
    this->update_move();
    this->update_attack();
    this->fireB->update();
}

void Rammus::set_player(Player *player) {
    this->p1 = player;
}


