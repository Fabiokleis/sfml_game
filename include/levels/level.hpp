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

                std::vector<Entities::Platform> platforms;
                std::vector<Entities::Wall> walls;
                std::vector<Entities::Coin> coins;
                std::vector<Entities::Spike> spikes;
                std::vector<float> check_points;

                std::vector<Entities::Characters::Dunga> dungas;
                Lista<Entities::Characters::Dunga> ListaDungas;

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
                void collision_manager(Entities::Player* other);
                static int generate_random(int low, int high);
                static std::string read_file(const std::string& filename);
                void save();
                void render();
                virtual void update() = 0;

                ListaEntidades* get_lista_entidades();
        };
}

#endif /* end of include guard: LEVEL_HPP_RTB6ZINA */
