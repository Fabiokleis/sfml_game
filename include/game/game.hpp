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
#include "menu.hpp"

class Game {
    private:
        Controllers::WindowServer window_server;
        Entities::Text *fps_text{};
        Entities::Player *player{};
        Controllers::Menu *menu{};

        sf::Clock clock{};
        float delta_time{};

        Maps::Map* map{};
        std::vector<Maps::Tile> tiles;
        std::vector<Maps::TileMap> tilemap;
        std::vector<Entities::Image> map_backgrounds;

        bool player_out_of_window();
        void init_entities();
        void init_map();
        void set_fps(float fps);
        void game_loop();
        void update_player_view();
        void handle_events();
        void update();
        void render_map();
        void render();
        void handle_collision();

    public:
        Game();
        ~Game();
        void exec();
};
#endif /* end of include guard: GAME_HPP_WSHRPK2N */
