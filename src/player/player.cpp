#include <iostream>
#include "player.hpp"
#include "config.h"


Player::Player(const float x, const float y) {
        this->init_texture(x, y);
        this->init_animations();
        this->init_physics();
}

Player::~Player() {

}

void Player::init_texture(const float x, const float y) {
    std::string path = RESOURCE_PATH;

    if (!this->texture.loadFromFile(path+"player/player_sprite.png")) {
        std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE FILE." << std::endl;
    }

    this->shape = sf::IntRect(0, 0, 48, 80);
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(this->shape);
    this->sprite.setPosition(x, y);
}

void Player::init_physics() {
    this->velocity_max = 2.f;
    this->velocity_min = 1.f;
    this->velocity_max_y = 1.f;
    this->acceleration = 2.f;
    this->gravity = 2.f;
    this->drag = 0.80f;
}

void Player::init_animations() {
    this->clock.restart();
    this->animation_switch = true;
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition() {
    return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds() {
    return this->sprite.getGlobalBounds();
}

bool Player::get_animation_switch() {
    bool anim_switch = this->animation_switch;

    if (this->animation_switch) {
        this->animation_switch = false;
    }

    return anim_switch;
}

void Player::move(const float dir_x, const float dir_y) {

    this->velocity.x = dir_x * this->acceleration;

    if (std::abs(this->velocity.x) > this->velocity_max) {
        this->velocity.x = this->velocity_max * ((this->velocity.x < 0.f) ? -1.f: 1.f);
    }
    this->sprite.move(this->velocity);
}

void Player::reset_animation_timer() {
    this->clock.restart();
    this->animation_switch = true;
}

void Player::update_physics() {

    this->velocity.y += 1 * this->gravity;

    if (std::abs(this->velocity.x) > this->velocity_max_y) {
        this->velocity.y = this->velocity_max_y * ((this->velocity.y < 0.f) ? -1.f: 1.f);
    }

    // deceleration velocity
    this->velocity.x *= this->drag;

    if (std::abs(this->velocity.x) < this->velocity_min) {
        this->velocity.x = 0.f;
    }
    if (std::abs(this->velocity.y) < this->velocity_min) {
        this->velocity.y = 0.f;
    }
    this->sprite.move(this->velocity);
}

void Player::update_animations() {

    
    if (this->animation_state == IDLE) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.1 || this->get_animation_switch()) {
            shape.top = 0;
            shape.left += 48;
            if (this->shape.left >= 96.f) {
                shape.left = 0;
            }

            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else if (this->animation_state == MOVING_LEFT) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08 || this->get_animation_switch()) {
            shape.top = 160;
            shape.left += 48;
            if (this->shape.left >= 96.f) {
                shape.left = 0;
            }

            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else if (this->animation_state == MOVING_RIGHT) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08 || this->get_animation_switch()) {
            shape.top = 80;
            shape.left += 48;
            if (this->shape.left >= 96.f) {
                shape.left = 0.f;
            }

            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }

    } else if (this->animation_state == JUMPING) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08 || this->get_animation_switch()) {
            shape.top = 240;
            shape.left = 0;
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else if (this->animation_state == MOVING_DOWN) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08 || this->get_animation_switch()) {
            shape.top = 400;
            shape.left = 0;
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else {
        this->clock.restart();
    }

}

void Player::update_input() {

    // player movement - kb
    this->animation_state = IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->animation_state = MOVING_LEFT;
        this->move(-1.f, 0.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->animation_state = MOVING_RIGHT;
        this->move(1.f, 0.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->animation_state = MOVING_DOWN;
        this->move(0.f, 1.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->animation_state = JUMPING;
        this->move(0.f, -1.f);
    }
}

void Player::update() {
    this->update_physics();
    this->update_input();
    this->update_animations();
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}