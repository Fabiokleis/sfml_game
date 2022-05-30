#include "image.hpp"
using namespace Entities;

Image::Image(const std::string& path_name) {
    this->load_texture(path_name);
}

Image::Image(double x, double y, double width, double height, sf::Color color) {
    this->set_size(width, height);
    this->set_position(x, y);
    this->set_color(color);
}

Image::Image(double x, double y, double width, double height, const std::string& path_name) {
    this->load_texture(path_name);
    this->set_size(width, height);
    this->set_position(x, y);
}


void Image::load_texture(const std::string &path_name) {
    this->texture = new sf::Texture();
    std::string path = RESOURCE_PATH;
    if (!this->texture->loadFromFile(path+path_name))
        std::cout << "ERROR:GAME::COULD NOT LOAD IMAGE TEXTURE." << std::endl;
    this->set_texture(this->texture);
    this->set_size(this->texture->getSize().x, this->texture->getSize().y);
}

Image::Image() {}
Image::~Image() {};
