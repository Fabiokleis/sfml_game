#ifndef GAME_HPP_WSHRPK2N
#define GAME_HPP_WSHRPK2N
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"
#include "config.h"
#include "map.hpp"
#include "tile.hpp"

class Game {
    private:
        sf::RenderWindow* window;
        sf::Event event;
        std::vector<sf::VideoMode> video_modes;
        sf::Sprite background;
        sf::Texture background_tex;
        sf::Clock clock;
        sf::Time total_time;
        float delta_time;
        sf::Text text;
        sf::Font font;
        std::vector<Maps::Tile> tiles;

        Maps::Map* map;

        Entities::Player *player;

        void init_window();
        void init_textures();
        void init_map();
        void init_player();
        void init_font();
        void init_objs();
        void set_fps(float fps);
        void game_loop();
        void handle_events();
        void render_bg();
        void render_text();
        void update();
        void render();
        void handle_collision();


    public:
        Game();
        ~Game();
        void exec();
};
#endif /* end of include guard: GAME_HPP_WSHRPK2N */
