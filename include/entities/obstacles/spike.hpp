#ifndef SPIKE_HPP_JIX7N9ST
#define SPIKE_HPP_JIX7N9ST
#include "obstacle.hpp"

namespace Entities::Obstacles {
        class Spike : public Obstacle {
            private:
                float scalar;

            public:
                Spike();

                Spike(Managers::GraphicManager *graphic_manager, sf::Texture *texture, double x, double y, double width,
                    double height, const std::string &path_name);

                void update();
                void scale();
                ~Spike();
        };
    }


#endif /* end of include guard: SPIKE_HPP_JIX7N9ST */
