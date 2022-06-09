#ifndef GRAPHIC_MANAGER_HPP_4SFJBDQ1
#define GRAPHIC_MANAGER_HPP_4SFJBDQ1
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "config.h"

namespace Managers {

    enum MenuStates {
        none = 0,
        restart,
        add_save,
        save,
        loading,
        level1,
        level2,
        credits,
        new_game,
        resume,
    };

    enum SubMenuStates {
        nones = 0,
        about,
        showkb,
    };

    class GraphicManager {
        private:
            sf::RenderWindow* window;
            sf::View view;
            sf::Event event;

        public:
            GraphicManager(const std::string& window_title);
            ~GraphicManager();
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

#endif /* end of include guard: GRAPHIC_MANAGER_HPP_4SFJBDQ1 */
