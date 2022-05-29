#ifndef MAIN_MENU_HPP_NMHFZTG6
#define MAIN_MENU_HPP_NMHFZTG6
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Controllers {
    enum MenuStates {
        restart = 0,
        loading,
        exit,
    };
    class MainMenu : public Menu {
        private:
            MenuStates state;
            bool saved_file;
            bool load_save;


        public:
            MainMenu(Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options);
            ~MainMenu();

            bool get_saved() const;
            bool get_load() const;

            MenuStates get_state();
            void update(bool from_game, bool from_player_dead) override;
            void events(WindowServer &window_server) override;
            void handle_events(WindowServer &window_server) override;
    };
}
#endif /* end of include guard: MAIN_MENU_HPP_NMHFZTG6 */
