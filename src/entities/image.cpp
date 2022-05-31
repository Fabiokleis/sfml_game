#include "image.hpp"
using namespace Entities;

Image::Image(Managers::GraphicManager &graphicManager, const std::string& path_name) :
    Entity(graphicManager), texture()
{
    this->load_texture(path_name);
}

Image::Image(Managers::GraphicManager &graphicManager, double x, double y, double width, double height, sf::Color color) :
        Entity(graphicManager)
{
    this->texture = nullptr;
    this->set_position(x, y);
    this->set_size(width, height);
    this->sprite.setFillColor(color);
}

Image::~Image() {}

void Image::load_texture(const std::string &path_name) {
    this->texture = new sf::Texture();
    std::string path = RESOURCE_PATH;
    if (!this->texture->loadFromFile(path+path_name))
        std::cout << "ERROR:GAME::COULD NOT LOAD IMAGE TEXTURE." << std::endl;

    this->sprite.setTexture(this->texture);
    this->sprite.setSize(sf::Vector2f(this->texture->getSize().x, this->texture->getSize().y));
}

void Image::update() {}
