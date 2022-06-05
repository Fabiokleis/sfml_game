#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "graphic_manager.hpp"
#include "player.hpp"
#include "config.h"
#include "obstacle.hpp"
#include "main_menu.hpp"
#include "sub_menu.hpp"
#include "obstacle.hpp"
#include "level1.hpp"

class Game {
    private:
        Managers::GraphicManager* graphic_manager;
        Entities::Player *jaime;

        Managers::MainMenu *menu;
        Managers::SubMenu *settings;

        Levels::Level1* level;

        Entities::Obstacle *life_image;
        sf::Texture *life_tex;
        Entities::Text *life_text;
        sf::Texture *coin_tex;
        Entities::Text *coin_number;
        Entities::Obstacle *coin_image;
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
        void init_level(const std::string& map_name);
        void set_time();
        void set_score(int coin, int life_number);
        void count_down();
        void restart_player();
        void game_loop(sf::Clock timer);
        void menu_loop(bool from_game = false, bool from_player_dead = false);
        void handle_resets();
        void update_player_view();
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
