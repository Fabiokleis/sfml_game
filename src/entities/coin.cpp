#include "coin.hpp"
using namespace Entities;

Coin::Coin(Managers::GraphicManager *graphic_manager, const std::string& coin_path, int id, double x, double y, double width, double height) :
    id(id), Obstacle(graphic_manager, coin_path)
{
    this->set_size(width, height);
    this->set_position(x, y);
}
Coin::Coin() : id(), Obstacle() {}
Coin::~Coin() {}

int Coin::get_id() const {
    return this->id;
}

void Coin::update() {}