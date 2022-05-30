#ifndef COIN_HPP_VCSQHMPZ
#define COIN_HPP_VCSQHMPZ
#include "image.hpp"
#include <SFML/Graphics.hpp>

namespace Entities {

    class Coin : public Image {
        private:
            int id;

        public:
            Coin(const std::string& coin_path, int id, double x, double y, double width, double height);
            int get_id() const;
            ~Coin();
    };
}


#endif /* end of include guard: COIN_HPP_VCSQHMPZ */
