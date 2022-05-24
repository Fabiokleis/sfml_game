#ifndef TILE_HPP_30AHWVXM
#define TILE_HPP_30AHWVXM
#include <iostream>
#include <SFML/Graphics.hpp>
#include "collider.hpp"

namespace Maps {

    class Tile {
        private:
            sf::RectangleShape body;
            std::string type;
        public:
            Tile(std::string type, float width, float left, float height, float top);
            ~Tile();
            Controllers::Collider get_collider();
            sf::RectangleShape get_body();
            std::string get_type();
    };
}
#endif /* end of include guard: TILE_HPP_30AHWVXM */
