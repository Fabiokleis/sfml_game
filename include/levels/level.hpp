#ifndef LEVEL_HPP_RTB6ZINA
#define LEVEL_HPP_RTB6ZINA
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <random>
#include "config.h"
#include "entie.hpp"
#include "characters/player.hpp"
#include "obstacles/platform.hpp"
#include "obstacles/wall.hpp"
#include "obstacles/coin.hpp"
#include "obstacles/spike.hpp"
#include "ListaEntities.h"
#include "characters/enemy.hpp"
#include "characters/dunga.hpp"


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
                int dungas_number;

                Lista<Entities::Obstacles::Platform> platforms;
                Lista<Entities::Obstacles::Wall> walls;
                Lista<Entities::Obstacles::Coin> coins;
                Lista<Entities::Obstacles::Spike> spikes;
                Lista<Entities::Characters::Dunga> dungas;

                ListaEntidades ListaEnti;

                float* pDeltaT;


            public:
                Level();
                Level(Managers::GraphicManager *graphic_manager, std::string map_name, float* pDeltaT);
                ~Level();

                void load_texture();
                double get_height() const;
                double get_width() const;
                std::string get_name();
                sf::RectangleShape get_sprite() const;
                void collision_manager(Entities::Characters::Player* other);
                static int generate_random(int low, int high);
                static std::string read_file(const std::string& filename);
                void save();
                void render();
                virtual void update() = 0;

                ListaEntidades* get_lista_entidades();
        };
}

#endif /* end of include guard: LEVEL_HPP_RTB6ZINA */
