#include "wall.hpp"
using namespace Entities;

Wall::Wall() : Obstacle() {}
Wall::Wall(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color) :
    Obstacle(graphic_manager, x, y, width, height, color)
{
    this->type = "wall";
}

Wall::~Wall() {}

void Wall::update() {}