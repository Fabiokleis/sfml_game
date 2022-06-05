#ifndef LEVEL_HPP_RTB6ZINA
#define LEVEL_HPP_RTB6ZINA
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "config.h"
#include "entie.hpp"
#include "player.hpp"
#include "platform.hpp"
#include "wall.hpp"
#include "coin.hpp"
#include "spike.hpp"

namespace Levels {

class Level : public Entities::Entie {

        protected:
            double x;
            double y;
            double height;
            double width;
            float gravity;
            std::string map_name;
            sf::Texture texture;
            sf::RectangleShape sprite;

            int platforms_number;
            int walls_number;
            int coins_number;
            int spikes_number;

            std::vector<Entities::Platform> platforms;
            std::vector<Entities::Wall> walls;
            std::vector<Entities::Coin> coins;
            std::vector<Entities::Spike> spikes;
            std::vector<float> check_points;


    
        public:
            Level();
            Level(Managers::GraphicManager *graphic_manager, std::string map_name);
            ~Level();

            void load_texture();
            double get_height() const;
            double get_width() const;
            std::string get_name();
            sf::RectangleShape get_sprite() const;
            void collision_manager(Entities::Player *other);
            static std::string read_file(const std::string& filename);
            void save();
            void render();
            virtual void update() = 0;
    };
}

#endif /* end of include guard: LEVEL_HPP_RTB6ZINA */
