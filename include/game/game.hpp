#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "window_server.hpp"
#include "player.hpp"
#include "config.h"
#include "map.hpp"
#include "tile.hpp"
#include "image.hpp"

class Game {
    private:
        Controllers::WindowServer window_server;
        Entities::Text *fps_text{};
        Entities::Player *player{};
        Entities::Image *background{};
//        std::vector<sf::VideoMode> video_modes;
        sf::Clock clock;
//        sf::Time total_time;
        float delta_time{};

        std::vector<Maps::Tile> tiles;

        Maps::Map* map{};


        void init_entities();
        void init_map();
        void set_fps(float fps);
        void game_loop();
        void handle_events();
        void update();
        void render();
        void handle_collision();

    public:
        Game();
        ~Game();
        void exec();
};
#endif /* end of include guard: GAME_HPP_WSHRPK2N */
