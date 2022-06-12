#ifndef OBSTACLE_HPP_V2MLPPAW
#define OBSTACLE_HPP_V2MLPPAW
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "entity.hpp"

namespace Entities::Obstacles {
        class Obstacle : public Entity {
            protected:
                std::string type;


            public:
                Obstacle();

                Obstacle(sf::Texture *texture, Managers::GraphicManager *graphic_manager, const std::string &path_name);

                Obstacle(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height,
                        sf::Color color = sf::Color::Black);

                ~Obstacle();

                void load_texture(sf::Texture *texture, const std::string &path_name);
                std::string get_type() const;
                void move(float dir_x, float dir_y);
                virtual void update();
        };
}


#endif /* end of include guard: OBSTACLE_HPP_V2MLPPAW */
