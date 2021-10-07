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
        sf::Texture* tile_texture_sheet;


    public:
        Map(const float, const unsigned max_x, const unsigned max_y);
        ~Map();
        void update();
        void render(sf::RenderTarget* target);

        void add_tile(const unsigned x, const unsigned y, const unsigned z);
        void remove_tile(const unsigned x, const unsigned y, const unsigned z);

};