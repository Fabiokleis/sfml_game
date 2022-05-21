#ifndef WINDOW_SERVER_HPP_4SFJBDQ1
#define WINDOW_SERVER_HPP_4SFJBDQ1
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "menu.hpp"
#include "map.hpp"
#include "text.hpp"
#include "image.hpp"
#define WINDOW_X 1280
#define WINDOW_Y 720
#define FPS 60

namespace Controllers {

    class WindowServer {
        private:
            sf::RenderWindow* window;
            sf::View view{};
            sf::Event event{};

        public:
            WindowServer(const std::string& window_title);
            ~WindowServer();
            bool is_open();
            bool poll_event();
            sf::Vector2f get_window_size();
            sf::Vector2f get_view_size();
            sf::RenderWindow* get_window();
            sf::Event& get_event();

        Controllers::Menu create_menu(Entities::Image& menu_image, sf::Vector2f position, std::vector<Entities::Text>& text_options);
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
            void set_view(sf::View view);
            void reset_view();
            void resize_view(sf::Vector2f size);
            void set_view_center(sf::Vector2f position);
            void move_view(sf::Vector2f dir);
            void clear();
            void render(const sf::Drawable& object);
    };
}
#endif /* end of include guard: WINDOW_SERVER_HPP_4SFJBDQ1 */
