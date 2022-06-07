#ifndef COIN_HPP_VCSQHMPZ
#define COIN_HPP_VCSQHMPZ
#include "obstacle.hpp"
#include <SFML/Graphics.hpp>

namespace Entities::Obstacles {
        class Coin : public Obstacle {
        private:
            int id;


        public:
            Coin();

            Coin(Managers::GraphicManager *graphic_manager, sf::Texture *texture, const std::string &coin_path, int id,
                 double x, double y, double width, double height);

            int get_id() const;

            void update();

            ~Coin();
        };
    }


#endif /* end of include guard: COIN_HPP_VCSQHMPZ */
