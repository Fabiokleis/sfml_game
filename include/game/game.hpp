#include <SFML/Graphics.hpp>
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

        Map* map;

        Player *player;

        void init_window();
        void init_textures();
        void init_map();
        void init_player();
        void init_objs();
        void game_loop();
        void handle_events();
        void render_bg();
        void update();
        void render();



    public:
        Game();
        ~Game();
        void exec();
};
