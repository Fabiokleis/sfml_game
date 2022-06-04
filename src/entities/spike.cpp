#include "spike.hpp"
using namespace Entities;

Spike::Spike() : Obstacle() {}

Spike::Spike(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height,  const std::string &path_name) :
    Obstacle(graphic_manager, path_name)
{
    this->load_texture(path_name);
    this->set_position(x, y);
    this->set_size(width, height);
    this->set_velocity(0.0f, 0.0f);
}

void Spike::update() {

}

Spike::~Spike()  {}
