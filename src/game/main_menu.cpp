#include "main_menu.hpp"
#include "level.hpp"
#include "character.hpp"

using namespace Managers;

MainMenu::MainMenu() : load_save(), state(), credit(), saved_file() {}

MainMenu::MainMenu(Managers::GraphicManager *graphic_manager, double x, double y) : Menu(graphic_manager), load_save(), state(restart), credit() {
    this->saved_file = this->verify_save();
    this->init_title();
    this->init_background(x, y);
    this->init_entries();
    this->init_score();
}

MainMenu::~MainMenu() {
    delete credit;
}

void MainMenu::init_title() {
    this->title = new Entities::Text(this->get_render(),
            FONT_PATH,
            80,
            WINDOW_X / 2 - 240.0f,
            100,
            sf::Color::White,
            1 << 1,
            sf::Color(95, 0, 160),
            2.0f,
            "Jaime Adventures");
}

void MainMenu::init_background(double x, double y) {
    this->menu_image = new Entities::Image(this->get_render(), 0, 0, WINDOW_X, WINDOW_Y, sf::Color::Black);
    this->menu_image->set_position(x, y);
}

void MainMenu::init_entries() {
    this->max_options = 7;
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 128.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "New Game"));

    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Load save"));

    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Level 1"));
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Level 2"));

    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 128.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Settings"));
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 192.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Credits"));
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 256.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Exit"));

    this->credit = new Entities::Text(this->get_render(),
            FONT_PATH,
            24,
            WINDOW_X / 2.0f - 480.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Desenvolvimento\n"
            "\n"
            "Fabio Henrique Kleis Ribas Correa, Francisco Luis Dunaiski Bruginski\n"
            "fabiohenrique@utfpr.edu.br, fbruginski@utfpr.edu.br\n"
            "\n"
            "Artes e Mapas\n"
            "\n"
            "Fabio Henrique Kleis Ribas Correa, Alessandro Kleis\n"
            "fabiohenrique@utfpr.edu.br"
    );

}

void MainMenu::init_score() {
    if (saved_file) {
        std::string path = RESOURCE_PATH;
        path += SAVE_PATH;
        std::string buf = Levels::Level::read_file(path);
        rapidjson::Document saved_file;
        saved_file.Parse(buf.c_str());

        std::string map_name = saved_file["map_name"].GetString();
        int coin = saved_file["coin"].GetInt();
        int life = saved_file["life"].GetInt();

        std::string life_number_text("life: ");
        life_number_text += std::to_string(life) + '\n';
        std::string coin_text("coins: ");
        coin_text += std::to_string(coin);
        map_name += '\n' + life_number_text + coin_text;


        this->score_text = new Entities::Text(this->get_render(),
                                              FONT_PATH,
                                              32,
                                              WINDOW_X / 2.0f + 128.0f,
                                              WINDOW_Y / 2.0f + 128.0f,
                                              sf::Color(192, 192, 192),
                                              0,
                                              sf::Color::Transparent,
                                              0.0f, map_name);

        this->score_text->set_attr(sf::Color(192, 192, 192), sf::Color(95, 0, 160), 1.0f, 0);
    } else {
        this->score_text = new Entities::Text();
    }
}


bool MainMenu::verify_save() {
    std::string path = RESOURCE_PATH;
    std::string buf = Levels::Level::read_file(path + "jaime/save_state.json");
    if (!buf.empty()) {
        return true;
    }
    return false;
}

Entities::Text& MainMenu::show_credit() {
    return *this->credit;
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


void MainMenu::update(bool from_game, bool from_player_dead) {
    // limit menu_counter to be in range of [0-max_options-1]
    this->menu_counter = this->menu_counter >= this->max_options-1 ? this->max_options-1 : this->menu_counter <= 0 ? 0 : this->menu_counter;
    this->from_player_dead = from_player_dead;
    this->from_game = from_game;

    // clear all texts attr and set by flag1
    for (auto &option : this->text_options) {
        option->reset();
        if (from_game) {
            if (option->get_string() == "New Game" || option->get_string() == "Restart") {
                option->set_text("Resume");
            }
        } else if(from_player_dead) {
            if (option->get_string() == "Resume" || option->get_string() == "New Game") {
                option->set_text("Restart");
            }
        }
    }

    switch (this->menu_counter) {
        case 0:
            this->text_options[0]->set_attr(sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 1:
            this->text_options[1]->set_attr(sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 2:
            this->text_options[2]->set_attr( sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 3:
            this->text_options[3]->set_attr( sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 4:
            this->text_options[4]->set_attr( sf::Color::White,sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 5:
            this->text_options[5]->set_attr( sf::Color::White,sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 6:
            this->text_options[6]->set_attr( sf::Color::White,sf::Color(95, 0, 160), 3.0f, 0);
            break;
        default:
            break;
    }
}

void MainMenu::events(GraphicManager &window_server) {
    // Menu input updates
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->inc_option();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->dec_option();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 5) {
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
        this->verify_save();
        if (saved_file) {
            std::cout << "load save opt" << std::endl;
            this->set_on_menu(false);
            this->load_save = true;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 4) {
        // settings
        std::cout << "settings opt" << std::endl;
        this->set_on_submenu(true);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 6) {
        // exit opt
        this->set_on_menu(false);
        std::cout << "Exit opt" << std::endl;
        window_server.close();

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 2) {
        // level 1
        std::cout << "level 1 opt" << std::endl;
        this->state = phase1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 3) {
        // level 2
        std::cout << "level 2 opt" << std::endl;
        this->state = phase2;
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->state = none;
        }
    }
}

void MainMenu::handle_events(GraphicManager &window_server) {
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

void MainMenu::render() {
    this->menu_image->render();
    this->title->render();
    if (state == Managers::credits) {
        this->credit->render();

    } else {
        for (auto &option : this->text_options) {
            option->render();
        }
        if (saved_file) {
            this->score_text->render();
        }
    }
}
