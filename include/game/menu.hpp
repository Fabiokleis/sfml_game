#ifndef MENU_HPP_S0BISRCL
#define MENU_HPP_S0BISRCL
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "graphic_manager.hpp"
#include "image.hpp"
#include "text.hpp"
#include "character.hpp"

namespace Managers {

    class Menu {
        private:
            bool on_menu;
            bool on_submenu;

        protected:
            Entities::Text *title;
            Entities::Image *menu_image;
            std::vector<Entities::Text*> text_options;
            int max_options;
            int menu_counter;
            bool from_game;
            bool from_player_dead;

            
        public:
            Menu();
            ~Menu();
            sf::RectangleShape get_sprite();
            int get_current_option() const;
            void inc_option();
            void dec_option();
            void set_on_menu(bool flag);
            bool get_on_menu() const;
            void set_on_submenu(bool flag);
            bool get_on_submenu() const;
            std::vector<Entities::Text*> get_options();
            Entities::Text get_title();
            virtual void update(bool from_game, bool from_player_dead) = 0;
            virtual void events(GraphicManager &window_server) = 0;
            virtual void handle_events(GraphicManager &window_server) = 0;
    };
}
#endif /* end of include guard: MENU_HPP_S0BISRCL */
