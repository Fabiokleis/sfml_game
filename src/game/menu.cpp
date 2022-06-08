#include "menu.hpp"
using namespace Managers;

Menu::Menu(Managers::GraphicManager *graphic_manager) : menu_image(), text_options(), title(), score_text(), Entie(graphic_manager) {
    this->menu_counter = 0;
    this->max_options = 0;
    this->on_menu = true;
    this->on_submenu = false;
    this->from_game = false;
    this->from_player_dead = false;
}

Menu::Menu() : menu_image(), text_options(), title(), score_text(), from_game(), on_menu(), from_player_dead(), menu_counter(), max_options(), on_submenu() {}

Menu::~Menu() {
    delete title;
    delete menu_image;
    delete score_text;
}

void Menu::update() {}

sf::RectangleShape Menu::get_sprite() {
    return this->menu_image->get_sprite();
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

bool Menu::get_on_submenu() const {
    return this->on_submenu;
}

void Menu::set_on_menu(bool flag) {
    this->on_menu = flag;
}

void Menu::set_on_submenu(bool flag) {
    this->on_submenu = flag;
}

std::vector<Entities::Text*> Menu::get_options() {
    return this->text_options;
}

Entities::Text Menu::get_title() {
    return *this->title;
}
