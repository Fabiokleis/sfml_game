#ifndef SUB_MENU_HPP_H7NHBPAJ
#define SUB_MENU_HPP_H7NHBPAJ
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Menus {
        
    class SubMenu : public Menu {
        private:
            Managers::SubMenuStates state;
            Entities::Text *about_text;
            Entities::Obstacles::Obstacle *keyboard_image;
            sf::Texture *kb_tex;


        public:
            SubMenu();
            SubMenu(Managers::GraphicManager *graphic_manager, double x, double y);
            ~SubMenu();

            Managers::SubMenuStates get_state();
            void init_background(double x, double y);
            void init_entries();
            void init_title();
            void render();
            void update(bool from_game, bool from_player_dead);
            void events(Managers::GraphicManager &window_server);
            void handle_events(Managers::GraphicManager &window_server);
    };
}

#endif /* end of include guard: SUB_MENU_HPP_H7NHBPAJ */
