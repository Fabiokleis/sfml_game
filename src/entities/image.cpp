#include "image.hpp"
using namespace Entities;

Image::Image(const std::string& path_name) {
    std::string path = RESOURCE_PATH;
    if (!this->texture.loadFromFile(path+path_name))
        std::cout << "ERROR:GAME::COULD NOT LOAD BACKGROUND TEXTURE." << std::endl;
    this->sprite.setTexture(&this->texture);
    this->sprite.setSize(sf::Vector2f(this->texture.getSize()));
}

Image::Image(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    this->sprite.setSize(size);
    this->sprite.setPosition(position);
    this->sprite.setFillColor(color);
}

Image::Image() = default;
Image::~Image() = default;
