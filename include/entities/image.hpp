#ifndef IMAGE_HPP_V2MLPPAW
#define IMAGE_HPP_V2MLPPAW
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "entity.hpp"

namespace Entities {

    class Image : public Entity {
        private:
            sf::Texture texture;

        public:
            Image(const std::string& path_name);
            ~Image();
    };
}


#endif /* end of include guard: IMAGE_HPP_V2MLPPAW */
