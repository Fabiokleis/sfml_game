#ifndef PLATFORM_HPP_KWHTQICM
#define PLATFORM_HPP_KWHTQICM
#include "obstacle.hpp"
#include "config.h"

namespace Entities {

    class Platform : public Obstacle {
        
        private:


        public:
            Platform();
            Platform(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color);
            ~Platform();

            void update();
    };
}

#endif /* end of include guard: PLATFORM_HPP_KWHTQICM */
