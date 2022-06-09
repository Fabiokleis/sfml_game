#include "obstacles/coin.hpp"
using namespace Entities::Obstacles;

Coin::Coin(Managers::GraphicManager *graphic_manager, sf::Texture *texture, const std::string &coin_path,
           double x, double y, double width, double height) :
    Obstacle(texture, graphic_manager, coin_path)
{
    this->set_size(width, height);
    this->set_position(x, y);
    this->set_origin(width/2.0f, height/2.0f);
    this->type = "coin";
}

Coin::Coin() : Obstacle() {}
Coin::~Coin() {}

void Coin::update() {}
