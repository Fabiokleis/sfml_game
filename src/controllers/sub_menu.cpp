#include "sub_menu.hpp"
using namespace Controllers;

SubMenu::SubMenu(Entities::Text &title, Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options) :
    Menu(title, menu_image, position, text_options)
{
    // default submenu
    this->set_on_menu(false);
}

SubMenu::~SubMenu() = default;

SubMenuStates SubMenu::get_state() {
    return state;
}

void SubMenu::update(bool from_game, bool from_player_dead) {
    // limit menu_counter to be in range of [0-max_options-1]
    this->menu_counter = this->menu_counter >= this->max_options-1 ? this->max_options-1 : this->menu_counter <= 0 ? 0 : this->menu_counter;

    // clear all texts attr and set by flag
    for (auto &option : this->text_options) {
        option.reset();
        if (from_game && from_player_dead) {
            if (option.get_string() == "Resume") {
                option.set_text("Restart");
            }
        }
    }
    switch (this->menu_counter) {
        case 0:
            this->text_options[0].set_attr(sf::Color::Green, sf::Color::White, 3.0f, 0);

            break;
        case 1:
            this->text_options[1].set_attr(sf::Color::Green, sf::Color::White, 3.0f, 0);

            break;
        case 2:
            this->text_options[2].set_attr(sf::Color::Green, sf::Color::White, 3.0f, 0);

            break;

        default:
            break;
    }
}

void SubMenu::events(WindowServer &window_server) {
    // Menu input updates
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->inc_option();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->dec_option();
    }
    // resume
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) && this->get_current_option() == 0) {
        this->set_on_menu(false);
        std::cout << "resume opt" << std::endl;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 1) {
        // about 1
        this->state = about;
        std::cout << "about opt" << std::endl;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 2) {
        // keyboard
        this->state = showkb;
        std::cout << "kb 2 opt" << std::endl;
    } else {
        this->state = none;
    }
}

void SubMenu::handle_events(WindowServer &window_server) {
    while (window_server.poll_event()) {
        switch (window_server.get_event().type) {
            case sf::Event::Closed:
                window_server.close();
                break;
            case sf::Event::Resized:
                window_server.resize_view(
                        sf::Vector2f(window_server.get_event().size.width, window_server.get_event().size.height));
                break;
            case sf::Event::KeyPressed: // any key pressed call events
                this->events(window_server);

                break;
            default:
                break;
        }
    }
}
