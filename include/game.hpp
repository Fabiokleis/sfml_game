#include <SFML/Graphics.hpp>
#include <vector>
#include "map.hpp"
#include "player.hpp"
#include "config.h"

#pragma once
class Game {
    private:
        sf::RenderWindow* window;
        sf::Sprite background;
        sf::Texture background_tex;
        sf::Event event;

        Map* map;
        Player *player;

        void init_window(int width, int height);
        void init_background();
        void init_map();
        void init_player();
        void game_loop();
        void update();
        void render();
        void handle_events();
        void update_window_collision();
        void render_bg();

    public:
        Game();
        ~Game();
        void exec();
};
