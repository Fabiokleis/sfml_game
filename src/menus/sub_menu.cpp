#include "sub_menu.hpp"
using namespace Menus;
using namespace Managers;

SubMenu::SubMenu() : state(), about_text(), keyboard_image() {}

SubMenu::SubMenu(Managers::GraphicManager *graphic_manager, double x, double y) :
    Menu(graphic_manager), state(), keyboard_image(), about_text()
{
    // default submenu
    this->set_on_menu(false);
    this->init_title();
    this->init_entries();
    this->init_background(x, y);
}

SubMenu::~SubMenu() {
    delete about_text;
    delete kb_tex;
    delete keyboard_image;
}

void SubMenu::init_title() {
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

void SubMenu::init_background(double x, double y) {
    this->menu_image = new Entities::Obstacles::Obstacle(this->get_render(), 0.0f, 0.0f, WINDOW_X, WINDOW_Y, sf::Color::Black);
    this->menu_image->set_position(x, y);
}

void SubMenu::init_entries() {
    this->max_options = 3;
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Resume"));
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "About"));
    this->text_options.emplace_back(new Entities::Text(this->get_render(),
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Show Controls"));

    this->kb_tex = new sf::Texture();
    this->keyboard_image = new Entities::Obstacles::Obstacle(this->kb_tex, this->get_render(), KEYBOARD);
    this->about_text = new Entities::Text(this->get_render(),
            FONT_PATH,
            24,
            WINDOW_X / 2.0f - 480.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "About\n\n\n"
            "Fabio Henrique Kleis Ribas Correa, Francisco Luis Dunaiski Bruginski\n"
            "fabiohenrique@utfpr.edu.br, fbruginski@utfpr.edu.br\n"
            "\n"
            "Disciplina: Tecnicas de Programacao - CSE20 / S3  - Prof. Dr. Jean M. Simao\n"
            "Departamento Academico de Informatica - DAINF - Campus de Curitiba\n"
            "Curso Bacharelado em: Engenharia da Computacao / Sistemas de Informacao\n"
            "Universidade Tecnologica Federal do Parana - UTFPR"

    );
}

SubMenuStates SubMenu::get_state() {
    return state;
}

void SubMenu::update(bool from_game, bool from_player_dead) {
    // limit menu_counter to be in range of [0-max_options-1]
    this->menu_counter = this->menu_counter >= this->max_options-1 ? this->max_options-1 : this->menu_counter <= 0 ? 0 : this->menu_counter;

    // clear all texts attr and set by flag
    for (auto &option : this->text_options) {
        option->reset();
        if (from_game && from_player_dead) {
            if (option->get_string() == "Resume") {
                option->set_text("Restart");
            }
        }
    }
    switch (this->menu_counter) {
        case 0:
            this->text_options[0]->set_attr( sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);
            break;
        case 1:
            this->text_options[1]->set_attr(sf::Color::White, sf::Color(95, 0, 160),  3.0f, 0);
            break;
        case 2:
            this->text_options[2]->set_attr(sf::Color::White, sf::Color(95, 0, 160), 3.0f, 0);
            break;
        default:
            break;
    }
}

void SubMenu::events(GraphicManager &window_server) {
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
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 1) {
        // about 1
        this->state = about;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->get_current_option() == 2) {
        // keyboard
        this->state = showkb;
    } else {
        this->state = nones;
    }
}

void SubMenu::handle_events(GraphicManager &window_server) {
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

void SubMenu::render() {
    this->get_render()->reset_view();
    this->menu_image->render();
    this->title->render();
    if (state == Managers::showkb) {
        this->keyboard_image->render();
    } else if (state == Managers::about) {
        this->about_text->render();
    } else {
        for (auto &option : this->text_options) {
            option->render();
        }
    }
    this->get_render()->display();
}