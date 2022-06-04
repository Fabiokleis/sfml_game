#ifndef OBSTACLE_HPP_V2MLPPAW
#define OBSTACLE_HPP_V2MLPPAW
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "entity.hpp"

namespace Entities {

    class Obstacle : public Entity {
        private:
            sf::Texture *texture;

        public:
            Obstacle();
            Obstacle(Managers::GraphicManager *graphic_manager, const std::string& path_name);
            Obstacle(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color=sf::Color::Black);
            void load_texture(const std::string& path_name);
            ~Obstacle();
            virtual void update();
    };
}


#endif /* end of include guard: OBSTACLE_HPP_V2MLPPAW */
