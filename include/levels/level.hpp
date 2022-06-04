#ifndef LEVEL_HPP_RTB6ZINA
#define LEVEL_HPP_RTB6ZINA
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "config.h"
#include "image.hpp"
#include "entie.hpp"
#include "player.hpp"

namespace Levels {

class Level : public Entities::Entie {
    
        private:
            int height;
            int width;
            int tile_height;
            int tile_width;

            std::string map_name;
            Entities::Image *background;

    
        public:
            Level();
            Level(Managers::GraphicManager *graphic_manager, const std::string& map_name);
            ~Level();
    
            void init_variables();
            int get_height() const;
            int get_width() const;
            int get_tile_width() const;
            int get_tile_height() const;
            std::string get_name();

            static std::string read_file(const std::string& filename);
            void collision_manager(Entities::Player *other);
            void update();
            void render();
    };
}

#endif /* end of include guard: LEVEL_HPP_RTB6ZINA */
