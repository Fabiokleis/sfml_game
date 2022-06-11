#ifndef COIN_HPP_VCSQHMPZ
#define COIN_HPP_VCSQHMPZ
#include "obstacle.hpp"
#include <SFML/Graphics.hpp>

namespace Entities::Obstacles {
        class Coin : public Obstacle {
            private:
                float rot;
                sf::Clock timer;
            public:
                Coin();

                Coin(Managers::GraphicManager *graphic_manager, sf::Texture *texture, const std::string &coin_path,
                    double x, double y, double width, double height);
                void update();
                void tick();
                ~Coin();
        };
    }


#endif /* end of include guard: COIN_HPP_VCSQHMPZ */
