#include "fireBall.h"

using namespace Entities;

FireBall::FireBall(Managers::GraphicManager *graphic_manager, float *delta_time):
                Entity(graphic_manager), isActive(false), maxTimeActive(100), timeActive(0), delta_time(delta_time), type("fireball")
{
    this->set_position(0, -50);
    this->init_texture();
    this->shape = sf::IntRect(0, 0, 32, 32);
    this->sprite.setSize(sf::Vector2f(32, 32));
    this->sprite.setTextureRect(shape);
    this->sprite.setTexture(this->texture);
    this->sprite.setOutlineThickness(1.0f);
    this->sprite.setOutlineColor(sf::Color::Red);
}

FireBall::FireBall() {

}

FireBall::~FireBall() {

}

void FireBall::shoot(sf::Vector2f pos, sf::Vector2f vel) {
    this->set_velocity(vel.x, vel.y);
    this->set_position(pos.x, pos.y-15);
    timeActive = 0.0;
    isActive = true;
}

void FireBall::update() {
    if(isActive){
        if (timeActive > maxTimeActive){
            isActive = false;
            timeActive = 0;
            this->set_position(0, -50);
        } else {
            this->sprite.move(this->velocity * (*this->delta_time));
            timeActive++;
        }
    } else {
    }
}

void FireBall::init_texture() {
    this->texture = new sf::Texture();
    std::string assets_path = RESOURCE_PATH;
    if (!this->texture->loadFromFile(assets_path+FIREBALL_PATH)) {
        std::cout << "ERROR::FIREBALL_PATH_TEXTURE:: COULD NOT LOAD TEXTURE FILE." << std::endl;
    }
}

void FireBall::move(float dir_x, float dir_y) {
}

std::string FireBall::get_type() {
    return type;
}

void FireBall::on_collision() {
    isActive = false;
    timeActive = 0;
    this->set_position(0, -50);
}


