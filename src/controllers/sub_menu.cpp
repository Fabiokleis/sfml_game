#include "sub_menu.hpp"
using namespace Controllers;

SubMenu::SubMenu(Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options) :
    Menu(menu_image, position, text_options)
{
    // default submenu
    this->set_on_menu(false);
}

SubMenu::~SubMenu() = default;

void SubMenu::update(bool from_game) {
    // limit menu_counter to be in range of [1-max_options]
    this->menu_counter = this->menu_counter > this->max_options ? this->max_options : this->menu_counter < 1 ? 1 : this->menu_counter;

    // clear all texts attr
    for (auto &option : this->text_options) {
        option.reset();
    }

    switch (this->menu_counter) {
        case 1:
            this->text_options[0].set_attr(sf::Color::Cyan, sf::Color::White, 3.0f, 0);
            break;
        case 2:
            this->text_options[1].set_attr(sf::Color::Cyan, sf::Color::White, 3.0f, 0);
            break;
        case 3:
            this->text_options[2].set_attr(sf::Color::Cyan, sf::Color::White, 3.0f, 0);
            break;
        case 4:
            this->text_options[3].set_attr(sf::Color::Cyan, sf::Color::White, 3.0f, 0);
            break;

        default:
            break;
    }
}

void SubMenu::handle_events(WindowServer &window_server) {
// Menu input updates

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->inc_option();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->dec_option();
    }
    // resume
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && this->get_current_option() == 1) {
        this->set_on_menu(false);
        std::cout << "resume opt" << std::endl;
    }
    // set fullscreen
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 2) {
        std::cout << "set fullscreen opt" << std::endl;
        window_server.set_fullscreen();
    }
    // mute
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 3) {
        std::cout << "mute opt" << std::endl;
    }
    // keyboard settings
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 4) {
//          this->on_menu = false;
        std::cout << "keyboard settings opt" << std::endl;
    }

}
