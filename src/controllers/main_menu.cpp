#include "main_menu.hpp"
#include "map.hpp"
#include "player.hpp"

using namespace Controllers;

MainMenu::MainMenu(Entities::Text &title, Entities::Image &menu_image, sf::Vector2f position, std::vector<Entities::Text> &text_options) :
    Menu(title, menu_image, position, text_options), load_save(), state(restart)
{
    std::string path = RESOURCE_PATH;
    std::string buf = Maps::Map::read_file(path+"player/save_state.json");
    if (!buf.empty()) {
        this->saved_file = true;

    } else {
        this->saved_file = false;
    }
}

MainMenu::~MainMenu() {}

void MainMenu::update(bool from_game, bool from_player_dead) {
    // limit menu_counter to be in range of [0-max_options-1]
    this->menu_counter = this->menu_counter >= this->max_options-1 ? this->max_options-1 : this->menu_counter <= 0 ? 0 : this->menu_counter;
    this->from_player_dead = from_player_dead;
    this->from_game = from_game;

    // clear all texts attr and set by flag1
    for (auto &option : this->text_options) {
        option.reset();
        if (from_game) {
            if (option.get_string() == "New Game" || option.get_string() == "Restart") {
                option.set_text("Resume");
            }
        } else if(from_player_dead) {
            if (option.get_string() == "Resume" || option.get_string() == "New Game") {
                option.set_text("Restart");
            }
        }
    }

    switch (this->menu_counter) {
        case 0:
            this->text_options[0].set_attr(sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);

            break;
        case 1:
            this->text_options[1].set_attr(sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);

            break;
        case 2:
            this->text_options[2].set_attr( sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);

            break;
        case 3:
            this->text_options[3].set_attr( sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);

            break;
        case 4:
            this->text_options[4].set_attr( sf::Color::White,sf::Color(95, 0, 160), 3.0f, 0);

            break;
        default:
            break;
    }
}

void MainMenu::events(WindowServer &window_server) {
    // Menu input updates
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->inc_option();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->dec_option();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 3) {
        // credits opt
        std::cout << "credits opt" << std::endl;
        this->state = credits;

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 0) {
        // start
        if (this->state == credits) {
            this->state = restart;
        } else {
            this->set_on_menu(false);
            if (this->from_player_dead) {
                // restart game
                std::cout << "restart opt" << std::endl;
                this->state = restart;
            } else {
                // new game
                std::cout << "new game opt" << std::endl;
                this->state = restart;
            }
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 1) {
        // load save opt
        this->state = loading;
        if (saved_file) {
            std::cout << "load save opt" << std::endl;
            this->set_on_menu(false);
            this->load_save = true;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 2) {
        // settings
        std::cout << "settings opt" << std::endl;
        this->set_on_submenu(true);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 4) {
        // exit opt
        this->set_on_menu(false);
        std::cout << "Exit opt" << std::endl;
        window_server.close();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->state = none;
        }
    }
}

void MainMenu::handle_events(WindowServer &window_server) {
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
                // default esc exit from main menu and the game!
                if (window_server.get_event().key.code == sf::Keyboard::Escape && this->state != none) {
                    window_server.close();
                }
                break;
            default:
                break;
        }
    }
}

bool MainMenu::get_saved() const {
    return this->saved_file;
}

MenuStates MainMenu::get_state() {
    return this->state;
}

bool MainMenu::get_load() const {
    return this->load_save;
}

