#include "image.hpp"
using namespace Entities;

Image::Image(const std::string& path_name) {
    std::string path = RESOURCE_PATH;
    if (!this->texture.loadFromFile(path+path_name))
        std::cout << "ERROR:GAME::COULD NOT LOAD BACKGROUND TEXTURE." << std::endl;
    this->sprite.setTexture(&this->texture);
    this->set_size(sf::Vector2f(this->texture.getSize()));
}

Image::~Image() = default;
