#include "platform.hpp"
using namespace Entities;

Platform::Platform() : Obstacle(){}

Platform::Platform(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color) :
    Obstacle(graphic_manager, x, y, width, height, color)
{
    this->type = "platform";
}

Platform::~Platform() {}

void Platform::update() {}
