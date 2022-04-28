#include <iostream>
#include "player.hpp"
#include "config.h"


Player::Player(const float x, const float y) {
    this->init_texture(x, y);
    // this->init_animations();
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
    this->sprite.setTexture(&this->texture);
    this->sprite.setTextureRect(this->shape);
    this->sprite.setPosition(x, y);
    this->sprite.setSize(sf::Vector2f(48.0f, 80.0f));
}

void Player::init_physics() {
    this->velocity_max = 2.f;
    this->velocity_min = 1.f;
    this->velocity_max_y = 8.f;
    this->acceleration = 2.f;
    this->gravity = 1.f;
    this->drag = 0.80f;
    this->on_ground = false;
}

void Player::init_animations() {
    this->clock.restart();
    this->animation_switch = true;
}

void Player::set_position(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

sf::Vector2f Player::get_position() {
    return this->sprite.getPosition();
}

sf::FloatRect Player::get_bounds() {
    return this->sprite.getGlobalBounds();
}

sf::RectangleShape Player::get_body() {
    return this->sprite;
}

void Player::reset_velocity_y() {
    this->velocity.y = 0.f;
}

bool Player::get_animation_switch() {
    bool anim_switch = this->animation_switch;

    if (this->animation_switch) {
        this->animation_switch = false;
    }

    return anim_switch;
}

void Player::reset_animation_timer() {
    this->clock.restart();
    this->animation_switch = true;
}

void Player::set_current_key(KEYS_STATES key, bool flag) {
    this->state_key[key] = flag;
}

void Player::set_on_ground(bool flag) {
    this->on_ground = flag;
}

void Player::move(const float dir_x, const float dir_y) {

    this->velocity.x = dir_x * this->acceleration;

    if (std::abs(this->velocity.x) > this->velocity_max) {
        this->velocity.x = this->velocity_max * ((this->velocity.x < 0.f) ? -1.f: 1.f);
    }

    if (this->on_ground) {
        this->velocity.y = dir_y * this->acceleration * 8;
        this->set_on_ground(false);
    }

    this->sprite.move(this->velocity);
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

void Player::update_input() {

    // player movement - kb
    this->animation_state = IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->animation_state = MOVING_LEFT;
        this->move(-1.f, 0.f);
        this->set_current_key(LEFT, true);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->animation_state = MOVING_RIGHT;
        this->move(1.f, 0.f);
        this->set_current_key(RIGHT, true);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->animation_state = MOVING_DOWN;
        this->set_current_key(DOWN, true);
        // this->move(0.f, 1.f);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (this->on_ground)){
        this->animation_state = JUMPING;
        this->set_current_key(JUMP, true);
        this->move(0.f, -1.f);
    }

}

void Player::update_animations() {


    if (this->animation_state == IDLE) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08) {
            this->shape.top = 0;
            this->shape.left += 48;
            if (this->shape.left >= 96.f) {
                shape.left = 0;
            }
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else if (this->animation_state == MOVING_LEFT) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08) {
            this->shape.top = 160;
            this->shape.left += 48;
            if (this->shape.left >= 96.f) {
                this->shape.left = 0;
            }
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else if (this->animation_state == MOVING_RIGHT) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08) {
            this->shape.top = 80;
            this->shape.left += 48;
            if (this->shape.left >= 96.f) {
                this->shape.left = 0.f;
            }
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }

    } else if (this->animation_state == JUMPING) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08) {
            this->shape.top = 240;
            this->shape.left = 0;
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else if (this->animation_state == MOVING_DOWN) {
        if (this->clock.getElapsedTime().asSeconds() >= 0.08) {
            this->shape.top = 400;
            this->shape.left = 0;
            this->clock.restart();
            this->sprite.setTextureRect(this->shape);
        }
    } else {
        this->clock.restart();
    }


}

void Player::update_player_state() {

    this->last_state = this->animation_state;

}

void Player::update() {
    this->update_input();
    // this->update_animations();
    this->update_physics();
    this->update_player_state();
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}
