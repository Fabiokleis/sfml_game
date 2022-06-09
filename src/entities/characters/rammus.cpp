#include "characters/rammus.h"

using namespace Entities;
using namespace Entities::Characters;

Rammus::Rammus() {}

Rammus::Rammus(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
               int life_number, sf::Vector2u image_count, float switch_time, States state,
               const std::string &path_name, float *delta_time):
        Enemy(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time),
        id(id), cdr(150), moveMax(200)
{
    this->acceleration = 150.0f;
    this->velocity = sf::Vector2f(0,0);
    this->type = "rammus";
    this->attackTimer = 0;
    this->canAttack = 0;
    this->fireB = new FireBall(graphic_manager, delta_time);
}

Rammus::~Rammus() {

}

std::string Rammus::get_type() {
    return this->type;
}

int Rammus::get_id() const {
    return this->id;
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
    if(moveTimer >= moveMax && !moveleft){
        moveleft = true;
        this->move(1.0f, 0.0f);
        moveTimer = -moveMax;
    } else if (moveTimer > 0){
        this->move(-1.0f, 0.0f);
        moveleft = false;
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
    if (state == walking_left) {
        fireB->shoot(this->get_position(), sf::Vector2f(-300, 0));
    } else {
        fireB->shoot(this->get_position(), sf::Vector2f(300, 0));
    }
}

void Rammus::update() {
    //this->update_physics();
    this->update_animation();
    this->update_move();
    this->update_attack();
    this->fireB->update();

    if(velocity.x < 0){
        this->state = walking_left;
    }else if(velocity.x > 0){
        this->state = walking_right;
    }
    if(velocity.x == 0){
        this->state = idle;
    }
}


