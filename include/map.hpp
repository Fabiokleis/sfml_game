#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.hpp"


#pragma once
class Map {
    private:
        float grid_size_f;
        unsigned grid_size_u;
        sf::Vector2u max_size;
        unsigned layers;
        std::vector<std::vector<std::vector<Tile*>>> map;


    public:
        Map();
        ~Map();
        void update();
        void render(sf::RenderTarget* target);

};