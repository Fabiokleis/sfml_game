#include <iostream>
#include "player.hpp"
#include "config.h"


Player::Player() {
    this->init_texture();
    this->movement_speed = 5.f;
}

Player::~Player() {

}

void Player::init_texture() {
    std::string path = RESOURCE_PATH;
    if (!this->texture.loadFromFile(path+"fishing_boo_48x48.png")) {
        std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE FILE." << std::endl;
    };

    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(0.f, 0.f);
}

void Player::move(const float dirX, const float dirY) {
    this->sprite.move(this->movement_speed * dirX, this->movement_speed * dirY);
}

void Player::update_input() {

    // player movement - kb
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->move(-1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->move(0.f, 1.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->move(1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->move(0.f, -1.f);
    }
}

void Player::update_window_collision(sf::RenderTarget* target) {


}

void Player::update(sf::RenderTarget* target) {
    
    this->update_window_collision(target);
    
    this->update_input();
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}