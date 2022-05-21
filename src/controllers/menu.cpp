#include "menu.hpp"
using namespace Controllers;

Menu::Menu(Entities::Image& menu_image, sf::Vector2f position, std::vector<Entities::Text>& text_options) :
    menu_image(menu_image), text_options(text_options)
{
    this->menu_image.set_position(position);
}

Menu::~Menu() = default;

sf::RectangleShape Menu::get_sprite() {
    return this->menu_image.get_sprite();
}

void Menu::populate_option(Entities::Text &options) {
    this->text_options.push_back(options);
}
