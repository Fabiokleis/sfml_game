#include <iostream>
#include "player.hpp"
#include "config.h"
#include <math.h>


Player::Player(float x, float y) {
    this->init_texture(x, y);
    this->init_physics();
}

Player::~Player() {
    delete player_animation;
}

void Player::init_texture(const float x, const float y) {
    std::string path = RESOURCE_PATH;

    if (!this->texture.loadFromFile(path+"player/player_sprite.png")) {
        std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE FILE." << std::endl;
    }

    this->size = sf::Vector2f(44, 78);
    this->shape = sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y));
    this->sprite.setTexture(&this->texture);
    this->sprite.setTextureRect(this->shape);
    this->sprite.setPosition(x, y);
    this->sprite.setSize(size);
    this->sprite.setOrigin(size / 2.0f);
    this->sprite.setOutlineThickness(2.0f);
    this->sprite.setOutlineColor(sf::Color::Yellow);
    this->player_animation = new Animation(&this->texture, sf::Vector2u(3, 5), 0.12f);
}

void Player::init_physics() {
    this->velocity_max = 2.0f;
    this->velocity_min = 1.0f;
    this->velocity_max_y = 10.f;
    this->acceleration = 2.0f;
    this->gravity = 981.0f;
    this->drag = 0.70f;
    this->on_ground = false;
    this->collide = false;
    this->delta_time = 0.1;
}

void Player::set_collide(bool flag) {
    this->collide = flag;
}

sf::Vector2f Player::get_velocity() {
    return this->velocity;
}

Collider Player::get_collider() {
    return Collider(this->sprite);
}

void Player::reset_velocity_y() {
    this->velocity.y = 0.0f;
}

void Player::reset_clock(float dt) {
    this->delta_time = dt;
}

void Player::move(const float dir_x, const float dir_y) {

    this->velocity.x += dir_x * this->acceleration;

    if (std::abs(this->velocity.x) > this->velocity_max) {
        this->velocity.x = this->velocity_max * ((this->velocity.x < 0.f) ? -1.f: 1.f);
    }
    this->sprite.move(this->velocity);
}

void Player::update_physics() {

    this->velocity.y += this->gravity * this->delta_time;

    if (std::abs(this->velocity.y) > this->velocity_max_y) {
        this->velocity.y = this->velocity_max_y * ((this->velocity.y < 0.f) ? -1.f: 1.f);
    }

    // deceleration velocity
    this->velocity *= this->drag;

    if (std::abs(this->velocity.x) < this->velocity_min) {
        this->velocity.x = 0.f;
    }
    if (std::abs(this->velocity.y) < this->velocity_min) {
        this->velocity.y = 0.f;
    }

    this->sprite.move(this->velocity);
}

void Player::update_input() {

    // player movement - kb
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->move(-1.f, 0.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->move(1.f, 0.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        // this->move(0.f, 1.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->on_ground){
        this->move(0.f, -1.f);
        this->on_ground = false;
    }
}

void Player::update_animation() {

    if (this->velocity.x == 0.0f) {
        this->player_animation->update(0, this->delta_time, true);
    } else {

        if (this->velocity.x > 0.0f) {
            this->player_animation->update(1, this->delta_time, true);
        }
        if (this->velocity.x < 0.0f) {
            this->player_animation->update(1, this->delta_time, false);
        }
    }

    this->sprite.setTextureRect(this->player_animation->rect);
}

void Player::update() {
    this->update_input();
    this->update_physics();
    this->update_animation();
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}

