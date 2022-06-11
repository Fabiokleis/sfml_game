#include "obstacles/platform.hpp"
using namespace Entities::Obstacles;

Platform::Platform() : Obstacle() {}

Platform::Platform(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color) :
    Obstacle(graphic_manager, x, y, width, height, color), current_width(0)
{
    this->set_size(width, height);
    this->set_position(x, y);
    this->set_origin(width/2.0f, height/2.0f);
    this->type = "platform";
}

Platform::~Platform() {}

void Platform::decrease_width() {
    this->current_width = this->get_size().x - 1;
    if (this->current_width > 380) {
        this->set_size(current_width, this->get_size().y);
        this->set_origin(this->current_width/2.0f, this->get_size().y/2.0f);
    }
}

void Platform::update() {}
