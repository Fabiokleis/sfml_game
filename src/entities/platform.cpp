#include "platform.hpp"
using namespace Entities;

Platform::Platform() : Obstacle(){}

Platform::Platform(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color) :
    Obstacle(graphic_manager, x, y, width, height, color)
{
    this->set_size(width, height);
    this->set_position(x, y);
    this->set_origin(width/2.0f, height/2.0f);
    this->type = "platform";
}

Platform::~Platform() {}

void Platform::update() {}
