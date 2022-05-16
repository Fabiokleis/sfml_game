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

    if (!this->texture.loadFromFile(path+"player/player_sprite2.png")) {
        std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE FILE." << std::endl;
    }

    this->size = sf::Vector2f(45, 78);
    this->shape = sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y));
    this->sprite.setTexture(&this->texture);
    this->sprite.setTextureRect(this->shape);
    this->sprite.setPosition(x, y);
    this->sprite.setSize(size);
    this->sprite.setOrigin(size / 2.0f);
//    this->sprite.setOutlineThickness(2.0f);
//    this->sprite.setOutlineColor(sf::Color::Yellow);
    this->player_animation = new Animation(&this->texture, sf::Vector2u(3, 5), 0.12f);
}

void Player::init_physics() {
    this->velocity_max = 200.0f;
    this->velocity_min = 150.0f;
    this->velocity_max_y = 200.f;
    this->jump_height = 162.0f;
    this->acceleration = 200.0f;
    this->gravity = 981.0f;
    this->drag = 0.8f;
    this->delta_time = 0.1f;
    this->can_jump = false;
    this->state = falling;
}

sf::Vector2f& Player::get_velocity() {
    return this->velocity;
}

Collider Player::get_collider() {
    return Collider{this->sprite};
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
        this->velocity.y = 0.0f;
        state = ground;
        this->can_jump = true;
    } else if (this->velocity.y > 0.0f) {
        // collision on top
        this->velocity.y = 0.0f;
    }
}

void Player::move(const float dir_x, const float dir_y) {
    // accelerate
    this->velocity.x += dir_x * this->acceleration;

    // jump

    float jump = -((2 * dir_y) * this->gravity * this->jump_height);
    this->velocity.y = -sqrt(jump);
}

void Player::update_physics() {
    this->velocity.y += this->gravity * this->delta_time;

    if (std::abs(this->velocity.x) > this->velocity_max) {
        this->velocity.x = this->velocity_max * ((this->velocity.x < 0.f) ? -1.f: 1.f);
    }

    if (std::abs(this->velocity.x) < this->velocity_min) {
        this->velocity.x = 0.f;
    }
    if (std::abs(this->velocity.y) < this->velocity_min) {
        this->velocity.y = this->velocity_min;
    }
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
        this->state = jumping;
        this->can_jump = false;
        this->move(0.f, -1.f);
    }
}

void Player::update_animation() {

    if (this->player_animation) {

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


}

void Player::update() {
    this->update_input();
    this->update_physics();
    this->update_animation();
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}


