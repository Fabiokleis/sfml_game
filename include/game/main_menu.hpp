#ifndef MAIN_MENU_HPP_NMHFZTG6
#define MAIN_MENU_HPP_NMHFZTG6
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace Managers {

    enum MenuStates {
        none = 0,
        restart,
        loading,
        phase1,
        phase2,
        credits,
    };

    class MainMenu : public Menu {
        private:
            MenuStates state;
            bool saved_file;
            bool load_save;
            Entities::Text *credit;


    public:
            MainMenu();
            MainMenu(Managers::GraphicManager *graphic_manager, double x, double y);
            ~MainMenu();

            Entities::Text& show_credit();
            bool get_saved() const;
            bool get_load() const;
            bool verify_save();
            MenuStates get_state();
            void init_title();
            void init_entries();
            void init_background(double x, double y);
            void init_score();
            void render();
            void update(bool from_game, bool from_player_dead);
            void events(GraphicManager &window_server);
            void handle_events(GraphicManager &window_server);
    };
}
#endif /* end of include guard: MAIN_MENU_HPP_NMHFZTG6 */
