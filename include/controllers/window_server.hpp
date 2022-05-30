#ifndef WINDOW_SERVER_HPP_4SFJBDQ1
#define WINDOW_SERVER_HPP_4SFJBDQ1
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#define WINDOW_X 1280
#define WINDOW_Y 720
#define FPS 60
#define FONT_PATH "fonts/free_pixel.ttf"
#define PLAYER_SPRITE_PATH "player/player_sprite.png"
#define TIME 256
#define SAVE_PATH "player/save_state.json"
#define PLATFORM1 "destroyed_world.json"
#define PLATFORM2 "sorcerer_castle.json"
#define KEYBOARD "menu/keyboard.png"

namespace Controllers {

    class WindowServer {
        private:
            sf::RenderWindow* window;
            sf::View view;
            sf::Event event;

        public:
            WindowServer(const std::string& window_title);
            ~WindowServer();
            bool is_open();
            bool poll_event();
            sf::Vector2f get_window_size();
            sf::Vector2f get_view_size();
            sf::Event& get_event();
            void set_view(sf::View view);
            void reset_view();
            void resize_view(sf::Vector2f size);
            void clear();
            void close();
            void display();
            void render(const sf::Drawable& object);
    };
}

#endif /* end of include guard: WINDOW_SERVER_HPP_4SFJBDQ1 */
