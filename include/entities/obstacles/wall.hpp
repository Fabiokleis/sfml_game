#ifndef WALL_HPP_XKLPJ4FY
#define WALL_HPP_XKLPJ4FY
#include "obstacle.hpp"

namespace Entities {

    class Wall : public Obstacle {

        private:

        public:
            Wall();
            Wall(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color);
            ~Wall();
            void update();

    };
}



#endif /* end of include guard: WALL_HPP_XKLPJ4FY */
