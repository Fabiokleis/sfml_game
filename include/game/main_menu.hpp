#ifndef MAIN_MENU_HPP_NMHFZTG6
#define MAIN_MENU_HPP_NMHFZTG6
#include <SFML/Graphics.hpp>
#include "menu.hpp"

class MainMenu : public Menu {
    private:
        Managers::MenuStates state;
        bool saved_file;
        bool load_save;
        sf::String current_type;
        Entities::Text *credit;
        Entities::Text *save_options;
        Entities::Text *current_type_show;


    public:
        MainMenu();
        MainMenu(Managers::GraphicManager *graphic_manager, double x, double y);
        ~MainMenu();

        void add_save(const sf::String& new_save);
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
