#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "graphic_manager.hpp"
#include "player.hpp"
#include "config.h"
#include "level.hpp"
#include "object.hpp"
#include "image.hpp"
#include "main_menu.hpp"
#include "sub_menu.hpp"

class Game {
    private:
        Managers::GraphicManager* graphic_manager;
        Entities::Player *player;

        Managers::MainMenu *menu;
        Managers::SubMenu *settings;


        Entities::Text *score_text;


        Levels::Level* phase;
        std::vector<Levels::TileMap> tilemap;
        std::vector<Entities::Image> map_backgrounds;
        Levels::Object start_location;
        std::vector<Levels::Object> check_point_locations;
        Levels::Object end_location;
        Levels::Locations locations;
        Levels::Platforms platforms;
        Levels::Tiles tiles;
        Levels::Walls walls;

        std::vector<Entities::Coin> coins;
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
        void init_score();
        void parse_save(const std::string& buf);
        void init_phase(std::string map_name);
        void set_time();
        void set_score(int coin, int life_number);
        void count_down();
        void save_game(const Levels::Object& current_check_point);
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
        void render_phase();
        void render();
        void handle_collision();
        void handle_player_collision();

    public:
        Game();
        ~Game();
        void exec();

};
#endif /* end of include guard: GAME_HPP_WSHRPK2N */
