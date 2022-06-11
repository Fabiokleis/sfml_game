#include "obstacles/wall.hpp"
#include "level.hpp"
using namespace Entities::Obstacles;

Wall::Wall() : Obstacle() {}
Wall::Wall(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color) :
    Obstacle(graphic_manager, x, y, width, height, color)
{
    this->set_size(width, height);
    this->set_position(x, y);
    this->set_origin(width/2.0f, height/2.0f);
    this->type = "wall";
    this->current_height = Levels::Level::generate_random(10, 20);
}

Wall::~Wall() {}

// when player collide with wall the wall height increases 10~20 pixels
void Wall::increase_height() {
    

    if (this->sprite.getFillColor() != sf::Color::Cyan) {
        this->set_size(this->get_size().x, this->get_size().y + this->current_height);
        this->set_origin(this->get_size().x/2.0f, this->get_size().y / 2.0f);
    }
    this->set_color(sf::Color::Cyan);

}
void Wall::update() {}