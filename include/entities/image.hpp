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
            Image(const std::string& path_name);
            Image(double x, double y, double width, double height, sf::Color color=sf::Color::Black);
            Image(double x, double y, double width, double height, const std::string &path_name);
            void load_texture(const std::string& path_name);
            Image();
            ~Image();
    };
}


#endif /* end of include guard: IMAGE_HPP_V2MLPPAW */
