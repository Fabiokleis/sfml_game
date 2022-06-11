#include <iostream>
#include "game.hpp"
#include "level1.hpp"

Game::Game() :
        jaime(), level(), menu(), settings(), coin_image(), coin_number(), life_tex(),
        time_text(), total_time(TIME), life_image(), life_text(), on_menu(), level1(), level2(), coin_tex()
{
    this->graphic_manager = new Managers::GraphicManager("c++ game");
}

void Game::exec() {
    // setup game

    this->init_menu();
    this->menu_loop();

    if (this->graphic_manager->is_open() && !this->on_menu) {
        if (this->menu->get_state() == Managers::level1) {
            this->init_level(BACKGROUN_1);
        } else if (this->menu->get_state() == Managers::level2) {
            this->init_level(BACKGROUN_2);
        } else {
            this->init_level(BACKGROUN_1);
        }

        this->init_entities();
        // to init timer after load level and any other entity
        sf::Clock timer;
        this->game_loop(timer);
    }
}

Game::~Game() {
    delete jaime;
    delete level1;
    delete level2;
    delete settings;
    delete menu;
    delete graphic_manager;
    delete coin_image;
    delete coin_number;
    delete life_tex;
    delete coin_tex;
    delete life_image;
    delete life_text;
    delete score_text;
}


void Game::menu_loop(bool from_game, bool from_player_dead) {
    while (this->graphic_manager->is_open() && this->on_menu) {
        if (this->settings->get_on_menu()) {
            this->settings->handle_events(*this->graphic_manager);
            this->menu->set_on_submenu(this->settings->get_on_menu());
            this->settings->update(from_game, from_player_dead);
            this->settings->render();
        } else {
            this->on_menu = this->menu->get_on_menu();
            this->menu->handle_events(*this->graphic_manager);
            this->settings->set_on_menu(this->menu->get_on_submenu());
            this->menu->update(from_game, from_player_dead);
            this->menu->render();
        }
    }

}

void Game::game_loop(sf::Clock timer) {
    this->clock.restart();
    while (this->graphic_manager->is_open() && !this->on_menu) {
        float aux_time = timer.getElapsedTime().asSeconds();
        if (aux_time >= 1 && this->total_time > -1) {
            timer.restart();
            this->set_time();
        }

        Managers::GraphicManager::delta_time = this->clock.restart().asSeconds();
        this->set_score(this->jaime->get_coins(), this->jaime->get_life_number(), this->jaime->get_score());

        this->update();
        this->render();
    }
}

void Game::count_down() {
    if (this->total_time == -1) {
        this->jaime->set_state(Entities::Characters::dead);
    }
}

void Game::init_menu() {
    // game menu
    /*
    [0] New Game
    [1] save
    [2] Level 1
    [3] Level 2
    [4] Settings
        [0] Resume
        [1] About
        [2] Show Controls
    [5] Credits
    [6] Exit
    */
    this->on_menu = true;
    this->menu = new Menus::MainMenu(this->graphic_manager, 0, 0);
    this->settings = new Menus::SubMenu(this->graphic_manager, 0, 0);
}

void Game::init_entities() {

    // create a new jaime with save
    if (this->menu->get_load()) {


    } else {

        // create a new jaime without save
        this->jaime = new Entities::Characters::Player(
                this->graphic_manager,
                16,
                700,
                45, 80, 0, 0, 0, 5, sf::Vector2u(3, 6), 0.1f,
                Entities::Characters::idle,
                PLAYER_SPRITE_PATH,
                &Managers::GraphicManager::delta_time);
    }
    level->set_player(jaime);

    // life
    this->life_tex = new sf::Texture();
    this->life_image = new Entities::Obstacles::Obstacle(this->life_tex, this->graphic_manager, HEAD_SPRITE);
    this->life_image->set_position(32.0f, 32.0f);
    this->life_text = new Entities::Text(this->graphic_manager,
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color(255, 251, 232),
            0,
            sf::Color(0, 0, 0),
            2.0f,
            ""
            );

    // coins
    this->coin_tex = new sf::Texture();
    this->coin_image = new Entities::Obstacles::Obstacle(this->coin_tex, this->graphic_manager, COIN_PATH);
    this->coin_image->set_position(WINDOW_X - 64, 32.0f);
    this->coin_number = new Entities::Text(this->graphic_manager,
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color(255, 251, 232),
            0,
            sf::Color(0, 0, 0),
            2.0f,
            ""
            );
    this->score_text = new Entities::Text(this->graphic_manager,
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color(255, 251, 232),
            0,
            sf::Color(0, 0, 0),
            2.0f,
            ""
    );

    // time text
    this->time_text = new Entities::Text(this->graphic_manager,
            FONT_PATH,
            48,
            WINDOW_X / 2 - 32.0f,
            32.0f,
            sf::Color(255, 251, 232),
            0,
            sf::Color(0, 0, 0),
            2.0f,
            "");
}

void Game::init_level(const std::string& map_name) {
    if (map_name == BACKGROUN_1) {
        this->level1 = new Levels::Level1(this->graphic_manager, map_name);
        this->level2 = nullptr;
        this->level = static_cast<Levels::Level*>(this->level1);
    } else {
        this->level2 = new Levels::Level2(this->graphic_manager, map_name);
        this->level1 = nullptr;
        this->level = static_cast<Levels::Level*>(this->level2);
    }
}

void Game::set_score(int coin, int life_number, int score_number) {
    // coin update on screen
    sf::Vector2f pos(WINDOW_X, this->coin_image->get_sprite().getSize().y + 10.0f);
    pos.x -= 16;
    this->coin_number->set_position(pos);
    this->coin_number->set_text(std::to_string(coin));

    // score number
    this->score_text->set_position(sf::Vector2f(52.0f, 80.0f));
    std::string aux = std::to_string(score_number);
    this->score_text->set_text("Score: " + aux);

    // life update on screen
    sf::Vector2f pos_(this->life_image->get_sprite().getSize().x + 52.0f, this->life_image->get_sprite().getSize().y + 10.0f);
    this->life_text->set_position(pos_);
    this->life_text->set_text(std::to_string(life_number));
}

void Game::set_time() {
    // time update on screen
    this->time_text->set_position(sf::Vector2f(WINDOW_X / 2 - 32.0f, 32.0f));
    std::string aux = std::to_string(this->total_time);
    this->time_text->set_text("Time " + aux);
    this->total_time--;
}

void Game::handle_resets() {
    if (this->player_out_of_window()) {
        this->jaime->set_state(Entities::Characters::dead);
        this->jaime->update_life_number();
    }

    // verify if jaime dead and restart
    if (this->jaime->get_state() == Entities::Characters::dead) {
        this->menu->set_on_menu(true);
        this->on_menu = this->menu->get_on_menu();
        this->menu_loop(false, true); // create a specific flag to restart game
        this->on_menu = this->menu->get_on_menu();
        if (this->menu->get_state() == Managers::restart) {
            if (this->level->get_name() == BACKGROUN_1) {
                this->init_level(BACKGROUN_1);
            } else {
                this->init_level(BACKGROUN_2);
            }

        } else if (this->menu->get_state() == Managers::level1) {
            this->init_level(BACKGROUN_1);

        } else if (this->menu->get_state() == Managers::level2) {
            this->init_level(BACKGROUN_2);

        }
        this->restart_player();
    }
}

void Game::handle_collision() {
    // all collisions are triggered here
    this->level->handle_collision(this->jaime);
}

void Game::handle_events() {
    while (this->graphic_manager->poll_event()) {

        if (this->jaime->get_state() != Entities::Characters::dead) {
            this->jaime->handle_events(this->graphic_manager->get_event());
        }

        switch (this->graphic_manager->get_event().type) {

            case sf::Event::Closed:
                this->graphic_manager->close();
                break;

            case sf::Event::Resized:
                this->graphic_manager->resize_view(
                        sf::Vector2f(this->graphic_manager->get_event().size.width,
                        this->graphic_manager->get_event().size.height));
                break;
            case sf::Event::KeyPressed:
                // return to menu, automatically pause game loop
                if (this->graphic_manager->get_event().key.code == sf::Keyboard::Escape) {
                    this->menu->set_on_menu(true);
                    this->on_menu = this->menu->get_on_menu();
                    this->menu_loop(true);
                    this->on_menu = this->menu->get_on_menu();

                    if (this->menu->get_state() == Managers::level1) {
                        this->init_level(BACKGROUN_1);
                        this->restart_player();
                    } else if (this->menu->get_state() == Managers::level2) {
                        this->init_level(BACKGROUN_2);
                        this->restart_player();
                    }
                }
                break;
            default:
                break;
        }
    }
}

void Game::save() {
    // save here
}

bool Game::player_out_of_window() {
    auto map_height = this->level->get_height();
    auto map_width = this->level->get_width();

    // force jaime to stay in bottom/left/right position on level
    if (this->jaime->get_position().y > map_height || this->jaime->get_position().x > map_width || this->jaime->get_position().x < 0.0f) {
        return true;
    }
    return false;
}

void Game::update_player_view() {
    auto vhalfsize = this->graphic_manager->get_view_size() / 2.0f;
    auto map_height = this->level->get_height();
    auto map_width = this->level->get_width();
    sf::Vector2f view_pos(this->jaime->get_position());

    // force view to stay in level width, height, left and top
    if (!this->player_out_of_window()) {
        if (this->jaime->get_position().x + vhalfsize.x >= map_width) {
            view_pos.x = map_width - vhalfsize.x;
        } else if (this->jaime->get_position().x <= vhalfsize.x) {
            view_pos.x = vhalfsize.x;
        }
        if (this->jaime->get_position().y + vhalfsize.y >= map_height) {
            view_pos.y = map_height - vhalfsize.y;
        }
        this->graphic_manager->set_view(sf::View(view_pos, this->graphic_manager->get_window_size()));
    } else {
        this->graphic_manager->reset_view();
    }
}

void Game::update() {
    this->level->update();
    this->handle_events();
    this->jaime->update();
    this->count_down();
    this->handle_collision();
    this->handle_resets();
}

void Game::render() {
    // clear window each iteration
    this->graphic_manager->clear();

    // render level first
    this->level->render();
    this->graphic_manager->reset_view();

    // render objects to display information about score, time etc...
    this->score_text->render();
    this->graphic_manager->reset_view();
    this->coin_number->render();
    this->graphic_manager->reset_view();
    this->coin_image->render();
    this->graphic_manager->reset_view();
    this->time_text->render();
    this->graphic_manager->reset_view();
    this->life_text->render();
    this->graphic_manager->reset_view();
    this->life_image->render();
    this->graphic_manager->reset_view();

    // render jaime sprite, but he needs a different view size
    this->update_player_view();
    this->jaime->render();

    // finally, display everything
    this->graphic_manager->display();
}

void Game::restart_player() {
    this->jaime->restart(16, 900, this->jaime->get_coins(), this->jaime->get_life_number(), Entities::Characters::idle);
    level->set_player(jaime);
    this->total_time = TIME;
}

