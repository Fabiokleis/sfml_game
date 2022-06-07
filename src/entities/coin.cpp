#include "Obstacles/coin.hpp"
using namespace Entities;

Coin::Coin(Managers::GraphicManager *graphic_manager, sf::Texture *texture, const std::string &coin_path, int id,
           double x, double y, double width, double height) :
    Obstacle(texture, graphic_manager, coin_path), id(id)
{
    this->set_size(width, height);
    this->set_position(x, y);
    this->set_origin(width/2.0f, height/2.0f);
    this->type = "coin";
}

Coin::Coin() : id(), Obstacle() {}
Coin::~Coin() {}

int Coin::get_id() const {
    return this->id;
}

void Coin::update() {}
