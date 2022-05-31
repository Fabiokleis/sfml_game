#include "coin.hpp"
using namespace Entities;

Coin::Coin(Managers::GraphicManager &graphic_manager, const std::string& coin_path, int id, double x, double y, double width, double height) :
    id(id), Image(graphic_manager, coin_path)
{
    this->set_size(width, height);
    this->set_position(x, y);
}

Coin::~Coin() {}

int Coin::get_id() const {
    return this->id;
}

