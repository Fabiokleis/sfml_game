#include <iostream>
#include "character.hpp"
#include "player.hpp"
#include <cmath>

using namespace Entities;

Player::Player(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord, sf::Vector2u image_count, float switch_time, State state, const std::string& path_name) :
        Character(size, velocity, position, cord, image_count, switch_time, state, path_name)
{
    this->init_physics();
    this->sprite.setOutlineThickness(1.0f);
    this->sprite.setOutlineColor(sf::Color::Green);
}

Player::Player() = default;

Player::~Player() = default;

void Player::init_physics() {
    this->jump_height = 132.0f;
    this->acceleration = 200.0f;
    this->gravity = 981.0f;
//    this->drag = 0.8f;
    this->delta_time = 0.01f;
    this->can_jump = false;
}

void Player::reset_clock(float dt) {
    this->delta_time = dt;
}

void Player::on_collision() {
    if (this->velocity.x < 0.0f) {
        // collision on the left
        this->velocity.x = 0.0f;
        state = left;
    } else if (this->velocity.x > 0.0f) {
        // collision on the right
        this->velocity.x = 0.0f;
        state = right;
    }
    if (this->velocity.y < 0.0f) {
        // collision on the bottom
        state = ground;
        this->can_jump = true;
    } else if (this->velocity.y > 0.0f) {
        // collision on top
        this->state = falling;
    }
}

void Player::move(const float dir_x, const float dir_y) {
    // accelerate
    this->velocity.x += dir_x * this->acceleration;

    // jump
    if (this->state == jumping) {
        float jump = -((2 * dir_y) * this->gravity * this->jump_height);
        this->state = falling;
        this->velocity.y = static_cast<float>(-sqrt(static_cast<double>(jump)));
    }
}

void Player::update_physics() {
    this->velocity.y += this->gravity * this->delta_time;
    this->sprite.move(this->velocity * this->delta_time);
}

void Player::update_input() {
    this->velocity.x = 0.0f;
    // player movement - kb
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->move(-1.0f, 0.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->move(1.0f, 0.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->sprite.move(0.0f, 10.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->can_jump) {
        this->can_jump = false;
        this->move(0.f, -1.f);
    }
}

void Player::update_animation() {

    if (this->velocity.x == 0.0f) {
        this->get_animation().update(0, this->delta_time, true);
    } else {
        if (state != jumping && state != falling) {
            if (this->velocity.x > 0.0f) {
                this->get_animation().update(1, this->delta_time, true);
            }
            if (this->velocity.x < 0.0f) {
                this->get_animation().update(1, this->delta_time, false);
            }
        } else {
            if (this->state == jumping) {
                if (this->velocity.x > 0.0f) {
                    this->get_animation().update(2, this->delta_time, true);
                }
                if (this->velocity.x < 0.0f) {
                    this->get_animation().update(2, this->delta_time, false);
                }
            } else if(this->state == falling) {
                if (this->velocity.x > 0.0f) {
                    this->get_animation().update(3, this->delta_time, true);
                }
                if (this->velocity.x < 0.0f) {
                    this->get_animation().update(3, this->delta_time, false);
                }
            }
        }
    }
    this->set_rect(this->get_animation().rect);
}

void Player::update() {
    this->update_input();
    this->update_physics();
    this->update_animation();
}