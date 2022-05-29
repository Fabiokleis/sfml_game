#ifndef COIN_HPP_VCSQHMPZ
#define COIN_HPP_VCSQHMPZ
#include "image.hpp"
#include <SFML/Graphics.hpp>

namespace Entities {

    class Coin {
        private:
            int id;
            Entities::Image *image;

        public:
            Coin(int id, double x, double y, double width, double height);
            sf::RectangleShape get_sprite();
            int get_id() const;
            ~Coin();
    };
}


#endif /* end of include guard: COIN_HPP_VCSQHMPZ */
