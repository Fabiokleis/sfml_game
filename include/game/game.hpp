#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "graphic_manager.hpp"
#include "characters/player.hpp"
#include "config.h"
#include "obstacles/obstacle.hpp"
#include "main_menu.hpp"
#include "sub_menu.hpp"
#include "level1.hpp"
#include "level2.hpp"

class Game {
    private:
        Managers::GraphicManager* graphic_manager;
        Entities::Characters::Player *jaime;

        Menus::MainMenu *menu;
        Menus::SubMenu *settings;

        Levels::Level* level;
        Levels::Level1* level1;
        Levels::Level2* level2;

        Entities::Obstacles::Obstacle *life_image;
        sf::Texture *life_tex;
        Entities::Text *life_text;
        sf::Texture *coin_tex;
        Entities::Text *coin_number;
        Entities::Obstacles::Obstacle *coin_image;

        Entities::Text *score_text;
        Entities::Text *time_text;

        sf::Clock clock;

        int total_time;
        bool on_menu;


        bool player_out_of_window();
        void init_menu();
        void init_entities();
        void init_level(const std::string& map_name);
        void set_time();
        void save();
        void set_score(int coin, int life_number, int score_number);
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
