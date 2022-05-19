#ifndef WINDOW_SERVER_HPP_4SFJBDQ1
#define WINDOW_SERVER_HPP_4SFJBDQ1
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "map.hpp"
#include "text.hpp"
#include "image.hpp"

namespace Controllers {

    class WindowServer {
        private:
            sf::RenderWindow* window;
            sf::Event event{};

        public:
            WindowServer(unsigned size_x, unsigned size_y, unsigned fps, const std::string& window_title);
            ~WindowServer();
            bool is_open();
            bool poll_event();
            sf::RenderWindow* get_window();
            sf::Event& get_event();
            Entities::Player* create_player(
                    sf::Vector2f size,
                    sf::Vector2f velocity,
                    sf::Vector2f position,
                    sf::Vector2f cord,
                    sf::Vector2u image_count,
                    float switch_time,
                    Entities::State state,
                    const std::string& path_name);
            Maps::Map* create_map();
            Entities::Image* create_image(const std::string& path_name);
            Entities::Text* create_text(const std::string& path_name, unsigned size, float x, float y, sf::Color color);
            void clear();
            void render(const sf::Drawable& object);
    };
}
#endif /* end of include guard: WINDOW_SERVER_HPP_4SFJBDQ1 */
