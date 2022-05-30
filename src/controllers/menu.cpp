#include "menu.hpp"
using namespace Controllers;

Menu::Menu(Entities::Text &title, Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options) :
    menu_image(menu_image), text_options(text_options), title(title)
{
    this->menu_counter = 0;
    this->max_options = 0;
    this->menu_image.set_position(position);
    this->on_menu = true;
    this->on_submenu = false;
    this->from_game = false;
    this->from_player_dead = false;
}


Menu::~Menu() {}

sf::RectangleShape Menu::get_sprite() {
    return this->menu_image.get_sprite();
}


void Menu::populate_option(Entities::Text &options) {
    this->max_options++;
    this->text_options.push_back(options);
}

void Menu::dec_option() {
    this->menu_counter--;
}

void Menu::inc_option() {
    this->menu_counter++;
}

int Menu::get_current_option() const {
    return this->menu_counter;
}

bool Menu::get_on_menu() const {
    return this->on_menu;
}

void Menu::set_on_menu(bool flag) {
    this->on_menu = flag;
}

void Menu::set_on_submenu(bool flag) {
    this->on_submenu = flag;
}

bool Menu::get_on_submenu() const {
    return this->on_submenu;
}
