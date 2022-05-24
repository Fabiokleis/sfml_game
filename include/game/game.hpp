#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "window_server.hpp"
#include "player.hpp"
#include "config.h"
#include "map.hpp"
#include "object.hpp"
#include "tile.hpp"
#include "image.hpp"
#include "main_menu.hpp"
#include "sub_menu.hpp"

class Game {
    private:
        Controllers::WindowServer* window_server;
        Entities::Player *player{};

        std::vector<Entities::Text> menu_options{};
        Entities::Image *menu_bg{};
        Controllers::MainMenu *menu{};

        std::vector<Entities::Text> settings_options{};
        Entities::Image *settings_bg{};
        Controllers::SubMenu *settings{};

        Maps::Map* map{};
        std::vector<Maps::Tile> tiles;
        std::vector<Maps::TileMap> tilemap;
        std::vector<Maps::Object> locations;
        Maps::Object start_location;
        Maps::Object end_location;
        std::vector<Entities::Image> map_backgrounds;

        Entities::Text *fps_text{};
        sf::Clock clock{};
        float delta_time{};
        bool on_menu;

        bool player_out_of_window();
        void init_menu();
        void init_entities();
        void init_map();
        void menu_entries();
        void set_fps(float fps);
        void game_loop();
        void menu_loop(bool from_game = false);
        void update_player_view();
        void handle_events();
        void update();
        void render_menu();
        void render_settings();
        void render_map();
        void render();
        void handle_collision();

    public:
        Game();
        ~Game();
        void exec();
};
#endif /* end of include guard: GAME_HPP_WSHRPK2N */
