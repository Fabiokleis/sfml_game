#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.hpp>
#include <vector>
#include "player.hpp"
#include "config.h"
#include "map.hpp"

#pragma once
class Game {
    private:
        sf::RenderWindow* window;
        sf::Event event;
        std::vector<sf::VideoMode> video_modes;
        sf::Sprite background;
        sf::Texture background_tex;
        sf::Clock delta_clock;

        float delta;


        Map* map;

        Player *player;

        void init_window();
        void init_textures();
        void init_map();
        void init_player();
        void init_state();
        void game_loop();
        void update();
        void render();
        void handle_events();
        void update_window_collision();
        void render_bg();
        void update_delta();

    public:
        Game();
        ~Game();
        void exec();
};
