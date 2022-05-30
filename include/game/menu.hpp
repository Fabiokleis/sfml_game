#ifndef MENU_HPP_S0BISRCL
#define MENU_HPP_S0BISRCL
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "window_server.hpp"
#include "image.hpp"
#include "text.hpp"
#include "player.hpp"

namespace Controllers {

    class Menu {
        private:
            bool on_menu;
            bool on_submenu;

        protected:
            Entities::Text &title;
            Entities::Image &menu_image;
            std::vector<Entities::Text>& text_options;
            int max_options;
            int menu_counter;
            bool from_game;
            bool from_player_dead;

            
        public:
            Menu(Entities::Text &title, Entities::Image &menu_image, double x, double y, std::vector<Entities::Text> &text_options);
            ~Menu();
            sf::RectangleShape get_sprite();
            void populate_option(Entities::Text& options);
            int get_current_option() const;
            void inc_option();
            void dec_option();
            void set_on_menu(bool flag);
            bool get_on_menu() const;
            void set_on_submenu(bool flag);
            bool get_on_submenu() const;
            virtual void update(bool from_game, bool from_player_dead) = 0;
            virtual void events(WindowServer &window_server) = 0;
            virtual void handle_events(WindowServer &window_server) = 0;
    };
}
#endif /* end of include guard: MENU_HPP_S0BISRCL */
