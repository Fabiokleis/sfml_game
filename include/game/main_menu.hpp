#ifndef MAIN_MENU_HPP_NMHFZTG6
#define MAIN_MENU_HPP_NMHFZTG6
#include <SFML/Graphics.hpp>
#include "menu.hpp"

class MainMenu : public Menu {
    private:
        Managers::MenuStates state;
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
        Managers::MenuStates get_state();
        void init_title();
        void init_entries();
        void init_background(double x, double y);
        void init_score();
        void render();
        void update(bool from_game, bool from_player_dead);
        void events(Managers::GraphicManager &window_server);
        void handle_events(Managers::GraphicManager &window_server);
};

#endif /* end of include guard: MAIN_MENU_HPP_NMHFZTG6 */
