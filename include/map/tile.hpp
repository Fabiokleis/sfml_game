#include <iostream>
#include <SFML/Graphics.hpp>
#include "collider.hpp"

#pragma once
class Tile {
    private:
        sf::RectangleShape body;
    public:
        Tile(float width, float left, float height, float top);
        ~Tile();
        Collider get_collider();
};