#ifndef TILE_HPP_30AHWVXM
#define TILE_HPP_30AHWVXM
#include <iostream>
#include <SFML/Graphics.hpp>
#include "collider.hpp"

namespace Maps {

    class Tile {
        private:
            sf::RectangleShape body;

        public:
            Tile(float width, float left, float height, float top);
            ~Tile();
            Controllers::Collider get_collider();
            sf::RectangleShape get_body();
    };
}
#endif /* end of include guard: TILE_HPP_30AHWVXM */
