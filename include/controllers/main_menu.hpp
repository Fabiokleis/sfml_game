#ifndef MAIN_MENU_HPP_NMHFZTG6
#define MAIN_MENU_HPP_NMHFZTG6
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Controllers {

    class MainMenu : public Menu {
        private:
        public:
            MainMenu(Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options);
            ~MainMenu();
            void update(bool from_game) override;
            void events(WindowServer &window_server) override;
            void handle_events(WindowServer &window_server) override;
    };
}
#endif /* end of include guard: MAIN_MENU_HPP_NMHFZTG6 */
