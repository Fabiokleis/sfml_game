#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "window_server.hpp"
#include "player.hpp"
#include "config.h"
#include "map.hpp"
#include "object.hpp"
#include "image.hpp"
#include "main_menu.hpp"
#include "sub_menu.hpp"

class Game {
    private:
        Controllers::WindowServer* window_server;
        Entities::Player *player;

        Entities::Text *menu_title;
        std::vector<Entities::Text> menu_options;
        Entities::Image *menu_bg;
        Controllers::MainMenu *menu;

        std::vector<Entities::Text> settings_options;
        Entities::Image *settings_bg;
        Controllers::SubMenu *settings;
        Entities::Text *about;
        Entities::Image *showkb;

        Entities::Text *score_text;


        Maps::Map* map;
        std::vector<Maps::TileMap> tilemap;
        std::vector<Entities::Image> map_backgrounds;
        Maps::Object start_location;
        std::vector<Maps::Object> check_point_locations;
        Maps::Object end_location;
        Maps::Locations locations;
        Maps::Platforms platforms;
        Maps::Tiles tiles;
        Maps::Walls walls;

        std::vector<Entities::Coin> coins;
        Entities::Text *fps_text;
        Entities::Image *life_image;
        Entities::Text *life_text;
        Entities::Text *coin_number;
        Entities::Image *coin_image;
        Entities::Text *time_text;

        sf::Clock clock;
        float delta_time;
        int total_time;
        bool on_menu;


        bool player_out_of_window();
        bool verify_map();
        void init_menu();
        void init_entities();
        void parse_save(const std::string& buf);
        void init_map(std::string map_name);
        void menu_entries();
        void set_time();
        void set_fps(float fps);
        void set_score(int coin, int life_number);
        void count_down();
        void save_game(Maps::Object current_check_point);
        void restart_player();
        void game_loop(sf::Clock timer);
        void menu_loop(bool from_game = false, bool from_player_dead = false);
        void handle_resets();
        void update_player_view();
        void handle_events();
        void update();
        void next_map();
        void render_menu();
        void render_settings();
        void render_map();
        void render();
        void handle_collision();
        void handle_player_collision();

    public:
        Game();
        ~Game();
        void exec();

};
#endif /* end of include guard: GAME_HPP_WSHRPK2N */
