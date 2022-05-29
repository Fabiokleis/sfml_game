#ifndef SUB_MENU_HPP_H7NHBPAJ
#define SUB_MENU_HPP_H7NHBPAJ
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Controllers {

    enum SubMenuStates {
        none = 0,
        about,
        showkb
    };

    class SubMenu : public Menu {
        private:
            SubMenuStates state;

        public:
            SubMenu(Entities::Text &title, Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_optionss);
            ~SubMenu();

            SubMenuStates get_state();
            void update(bool from_game, bool from_player_dead) override;
            void events(WindowServer &window_server) override;
            void handle_events(WindowServer &window_server) override;
    };
}


#endif /* end of include guard: SUB_MENU_HPP_H7NHBPAJ */
