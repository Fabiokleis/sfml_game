#include <iostream>
#include "player.hpp"
#include "config.h"


Player::Player() {
    this->init_texture();
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

void Player::update() {

}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}