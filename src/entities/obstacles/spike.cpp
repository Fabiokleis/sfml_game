#include "obstacles/spike.hpp"
using namespace Entities::Obstacles;

Spike::Spike() : Obstacle() {}

Spike::Spike(Managers::GraphicManager *graphic_manager, sf::Texture *texture, double x, double y, double width,
             double height, const std::string &path_name) : Obstacle(texture, graphic_manager, path_name) {

    this->set_size(width, height);
    this->set_position(x, y);
    this->set_origin(width/2.0f, height/2.0f);
    this->type = "spike";
}


Spike::~Spike() {}

void Spike::update() {

}