#ifndef WINDOW_SERVER_HPP_4SFJBDQ1
#define WINDOW_SERVER_HPP_4SFJBDQ1
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "config.h"

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
