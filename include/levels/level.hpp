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
#include "characters/zezinho.h"
#include "characters/rammus.h"
#include "collision_manager.hpp"


namespace Levels {

    class Level : public Entie {

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
                int zezinho_number;
                int rammus_number;

                Managers::CollisionManager collision_manager;

                Listas::Lista<Entities::Obstacles::Platform> platforms;
                Listas::Lista<Entities::Obstacles::Wall> walls;
                Listas::Lista<Entities::Obstacles::Coin> coins;
                Listas::Lista<Entities::Obstacles::Spike> spikes;
                Listas::Lista<Entities::Characters::Dunga> dungas;
                Listas::Lista<Entities::Characters::Zezinho> listaZe;
                Listas::Lista<Entities::Characters::Rammus> listaRammus;
                Listas::Lista<Entities::FireBall> listaFB;


                std::vector<Entities::Characters::Enemy*> enemies;
                Listas::Lista<Entities::Obstacles::Obstacle> obstacles;
                Listas::ListaEntidades ListaEnti;

                float* pDeltaT;


            public:
                Level(Managers::GraphicManager *graphic_manager, std::string map_name, float* pDeltaT);
                ~Level();

                void load_texture();
                double get_height() const;
                double get_width() const;
                std::string get_name();
                void handle_collision(Entities::Characters::Player* other);
                static int generate_random(int low, int high);
                static std::string read_file(const std::string& filename);
                void render();
                virtual void update() = 0;

                Listas::ListaEntidades* get_lista_entidades();
        };
}

#endif /* end of include guard: LEVEL_HPP_RTB6ZINA */
