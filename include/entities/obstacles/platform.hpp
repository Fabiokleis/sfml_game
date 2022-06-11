#ifndef PLATFORM_HPP_KWHTQICM
#define PLATFORM_HPP_KWHTQICM
#include "obstacle.hpp"
#include "config.h"

namespace Entities::Obstacles {
        class Platform : public Obstacle {

            private:
                float current_width;
                
            public:
                Platform();

                Platform(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height,
                        sf::Color color);

                ~Platform();
                
                void decrease_width();
                void update();
        };
    }

#endif /* end of include guard: PLATFORM_HPP_KWHTQICM */
