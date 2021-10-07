#include <SFML/Graphics.hpp>
#include <vector>
#include "map.hpp"
#include "player.hpp"
#include "config.h"

#pragma once
class Game {
    private:
        sf::RenderWindow* window;
        std::vector<sf::VideoMode> video_modes;
        sf::Sprite background;
        sf::Texture background_tex;
        sf::Event event;
        sf::Clock delta_clock;
        float delta;

        Map* map;
        Player *player;

        void init_window();
        void init_textures();
        void init_map();
        void init_player();
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
