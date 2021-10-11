#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.hpp>
#include "player.hpp"
#include "tile.hpp"
#include "config.h"

#pragma once
class Map {

    private:
        sf::Vector2u tile_size;
        sf::Vector2u map_bounds;
        std::vector<tmx::MapLayer> layers;
        tmx::MapLoader* ml;


    public:
        Map();
        ~Map();

        sf::Vector2u get_bounds();

        void init_ml();
        void load_map();
        void init_variables();
        void map_collision(Player* player);
        void render(sf::RenderTarget* target);
        void update(Player* player);

};