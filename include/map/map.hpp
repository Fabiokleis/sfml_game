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
        tmx::MapObjects objs;



    public:
        Map();
        ~Map();

        sf::Vector2u get_bounds();
        tmx::MapObjects get_objs();
        sf::Vector2u get_tile_size();

        void init_ml();
        void load_map();
        void init_variables();
        void map_objs();
        void set_objs(tmx::MapObject obj);
        void render(sf::RenderTarget* target);
        void update();

};