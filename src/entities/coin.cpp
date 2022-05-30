#include "coin.hpp"
using namespace Entities;

Coin::Coin(const std::string& coin_path, int id, double x, double y, double width, double height) :
    id(id), Image(x, y, width, height, coin_path)
{

}

Coin::~Coin() {}

int Coin::get_id() const {
    return this->id;
}

