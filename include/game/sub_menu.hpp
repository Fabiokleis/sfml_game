#ifndef SUB_MENU_HPP_H7NHBPAJ
#define SUB_MENU_HPP_H7NHBPAJ
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Managers {

    enum SubMenuStates {
        nones = 0,
        about,
        showkb,
    };

    class SubMenu : public Menu {
        private:
            SubMenuStates state;
            Entities::Text *about_text;
            Entities::Image *keyboard_image;


    public:
            SubMenu();
            SubMenu(Managers::GraphicManager *graphic_manager, double x, double y);
            ~SubMenu();

            Entities::Image& show_kb();
            Entities::Text& show_about();
            SubMenuStates get_state();
            void init_background(double x, double y);
            void init_entries();
            void init_title();
            void init_score();
            void render();
            void update(bool from_game, bool from_player_dead);
            void events(GraphicManager &window_server);
            void handle_events(GraphicManager &window_server);
    };
}


#endif /* end of include guard: SUB_MENU_HPP_H7NHBPAJ */
