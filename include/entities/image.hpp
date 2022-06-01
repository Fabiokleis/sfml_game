#ifndef IMAGE_HPP_V2MLPPAW
#define IMAGE_HPP_V2MLPPAW
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "entity.hpp"

namespace Entities {

    class Image : public Entity {
        private:
            sf::Texture *texture;

        public:
            Image();
            Image(Managers::GraphicManager *graphic_manager, const std::string& path_name);
            Image(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, sf::Color color=sf::Color::Black);
            void load_texture(const std::string& path_name);
            ~Image();
            void update();
    };
}


#endif /* end of include guard: IMAGE_HPP_V2MLPPAW */
