#include "characters/enemy.hpp"

using namespace Entities::Characters;

Enemy::Enemy() {

}

Enemy::Enemy(Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                         int life_number, sf::Vector2u image_count, float switch_time, States state,
                         const std::string &path_name, float* delta_time) :
                         Character(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time), id()
{
    this->set_origin(width/2, height/2);
}

Enemy::~Enemy() {}

void Enemy::on_collision(const std::string &object_type) {
    if (object_type == "player") {
        if (collide_state == top) {
            state = dead;
        }
    }
    this->update_life_number();
}

void Enemy::update_life_number() {
    if(state == dead){
        this->life_number--;
    }
}

void Enemy::update_physics() {
    this->velocity.y += this->gravity;
    this->sprite.move(this->velocity * (*this->delta_time));
}

int Enemy::get_id() const {
    return this->id;
}

bool Enemy::operator==(Enemy &other) {
    return this->id == other.get_id();
}
