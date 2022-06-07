#include "obstacles/obstacle.hpp"
using namespace Entities::Obstacles;

Obstacle::Obstacle( sf::Texture *texture, Managers::GraphicManager *graphic_manager, const std::string& path_name) :
    Entity(graphic_manager)
{
    this->type = "obstacle";
    this->load_texture(texture, path_name);
}
Obstacle::Obstacle() {}
Obstacle::Obstacle(Managers::GraphicManager *graphicManager, double x, double y, double width, double height, sf::Color color) :
        Entity(graphicManager)
{
    this->set_position(x, y);
    this->set_size(width, height);
    this->sprite.setFillColor(color);
}

Obstacle::~Obstacle() {}

void Obstacle::load_texture(sf::Texture *texture, const std::string &path_name) {
    std::string path = RESOURCE_PATH;
    if (!texture->loadFromFile(path+path_name))
        std::cout << "ERROR::OBSTACLE::COULD NOT LOAD IMAGE TEXTURE." << std::endl;

    this->sprite.setTexture(texture);
    this->sprite.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
}

void Obstacle::update() {}

std::string Obstacle::get_type() const {
    return this->type;
}

void Obstacle::move(float dir_x, float dir_y) {
    this->sprite.move(dir_x, dir_y);
}
