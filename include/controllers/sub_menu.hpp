#ifndef SUB_MENU_HPP_H7NHBPAJ
#define SUB_MENU_HPP_H7NHBPAJ
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Controllers {

    class SubMenu : public Menu {
        private:

        public:
            SubMenu(Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options);
            ~SubMenu();
            void update(bool from_game) override;
            void handle_events(WindowServer &window_server) override;
    };
}


#endif /* end of include guard: SUB_MENU_HPP_H7NHBPAJ */
