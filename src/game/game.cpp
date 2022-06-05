#include <iostream>
#include "game.hpp"
#include "level1.hpp"
#include <fstream>

Game::Game() :
        jaime(), level(), menu(), settings(), delta_time(), coin_image(), coin_number(),
        time_text(), total_time(TIME), life_image(), life_text(), on_menu()
{
    this->graphic_manager = new Managers::GraphicManager("c++ game");

}

void Game::exec() {
    // setup game

    this->init_menu();
    this->menu_loop();

    if (this->graphic_manager->is_open() && !this->on_menu) {

//        // only load saved level if menu load save is selected
//        if (this->menu->get_saved() && this->menu->get_state() != Managers::restart) {
//            // verify if saved level is first or second
//            if (this->verify_map()) {
//                this->init_level(PLATFORM1);
//            } else {
//                this->init_level(PLATFORM2);
//            }
//        } else {
//            // default first level when not save found and not from load
//            this->init_level(PLATFORM1);
//        }
        this->init_level(BACKGROUN_1);
        this->init_entities();
        // to init timer after load level and any other entity
        sf::Clock timer;
        this->game_loop(timer);
    }
}

Game::~Game() {
    delete jaime;
    delete level;
    delete settings;
    delete menu;
    delete graphic_manager;
    delete coin_image;
    delete coin_number;
    delete life_tex;
    delete coin_tex;
    delete life_image;
    delete life_text;
}


void Game::menu_loop(bool from_game, bool from_player_dead) {
    while (this->graphic_manager->is_open() && this->on_menu) {
        if (this->settings->get_on_menu()) {
            this->settings->handle_events(*this->graphic_manager);
            this->menu->set_on_submenu(this->settings->get_on_menu());
            this->settings->update(from_game, from_player_dead);
            this->settings->render();
        } else {
            std::cout << "state: " << this->menu->get_state() << std::endl;
            this->on_menu = this->menu->get_on_menu();
            this->menu->handle_events(*this->graphic_manager);
            this->settings->set_on_menu(this->menu->get_on_submenu());
            this->menu->update(from_game, from_player_dead);
            this->menu->render();
        }
    }

}
//
//bool Game::verify_map() {
//    std::string path = RESOURCE_PATH;
//    std::string buf = Levels::Level::read_file(path + SAVE_PATH);
//    rapidjson::Document saved_file;
//    saved_file.Parse(buf.c_str());
//    std::string map_name = saved_file["map_name"].GetString();
//    if (map_name == PLATFORM1) {
//        return true;
//    }
//    return false;
//}

void Game::game_loop(sf::Clock timer) {
    this->clock.restart();
    while (this->graphic_manager->is_open() && !this->on_menu) {
        float aux_time = timer.getElapsedTime().asSeconds();
        if (aux_time > 1 && this->total_time >= 0) {
            this->set_time();
            timer.restart();
        }

        this->delta_time = this->clock.restart().asSeconds();
        this->jaime->reset_clock(delta_time);
        this->set_score(this->jaime->get_coins(), this->jaime->get_life_number());

        this->update();
        this->render();
    }
}

void Game::count_down() {
    if (this->total_time == -1) {
        this->jaime->set_state(Entities::dead);
    }
}

void Game::init_menu() {
    // game menu
    /*
    [0] New Game
    [1] Load save
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
    this->menu = new Managers::MainMenu(this->graphic_manager, 0, 0);
    this->settings = new Managers::SubMenu(this->graphic_manager, 0, 0);
}

void Game::init_entities() {

    // create a new jaime with save
    if (this->menu->get_load()) {
//        std::string path = RESOURCE_PATH;
//        std::string buf = Levels::Level::read_file(path + SAVE_PATH);
//        this->parse_save(buf);
//        std::string map_name = this->level->get_name();
//        // restart level
//        this->init_level(map_name);
//        // restart time
//        this->total_time = TIME;

    } else {

        // create a new jaime without save
        this->jaime = new Entities::Player(
                this->graphic_manager,
                100,
                200,
                45, 80, 0, 0, 0, 5, sf::Vector2u(3, 6), 0.1f,
                Entities::idle,
                PLAYER_SPRITE_PATH);
    }

    // life
    this->life_tex = new sf::Texture();
    this->life_image = new Entities::Obstacle(this->life_tex, this->graphic_manager, HEAD_SPRITE);
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
    this->coin_image = new Entities::Obstacle(this->coin_tex, this->graphic_manager, COIN_PATH);
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
    this->level = new Levels::Level1(this->graphic_manager, map_name);
}

void Game::set_score(int coin, int life_number) {
    // coin update on screen
    sf::Vector2f pos(WINDOW_X, this->coin_image->get_sprite().getSize().y + 10.0f);
    pos.x -= 16;
    this->coin_number->set_position(pos);
    this->coin_number->set_text(std::to_string(coin));

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
        this->jaime->set_state(Entities::dead);
        this->jaime->update_life_number();
    }

    // verify if jaime dead and restart
    if (this->jaime->get_state() == Entities::dead) {
        this->menu->set_on_menu(true);
        this->on_menu = this->menu->get_on_menu();
        this->menu_loop(false, true); // create a specific flag to restart game
        // out of the menu, after select a restart option
        //this->restart_player();
        this->on_menu = this->menu->get_on_menu();

    }
}

void Game::handle_collision() {
    // all collisions are triggered here
    this->level->collision_manager(this->jaime);
}

void Game::handle_events() {
    while (this->graphic_manager->poll_event()) {

        if (this->jaime->get_state() != Entities::dead) {
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
                    //this->restart_player();
                }
                break;
            default:
                break;
        }
    }
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

//
//void Game::parse_save(const std::string& buf) {
//    // parse json saved file to be a new instance of jaime and level
//
//
//
//    int coin = saved_file["coin"].GetInt();
//    int life = saved_file["life"].GetInt();
//    double x = saved_file["x"].GetDouble();
//    double y = saved_file["y"].GetDouble();
//    int time = saved_file["time"].GetInt();
//    this->total_time = time;
//    std::string map_name = saved_file["map_name"].GetString();
//
//    if (this->jaime) {
//        this->jaime->restart(x, y, coin, life, Entities::idle);
//    } else {
//        this->jaime = new Entities::Player(this->graphic_manager,
//                x, y, 45, 80,  0, 0, coin,life,
//                sf::Vector2u(3, 6), 0.1f, Entities::idle, PLAYER_SPRITE_PATH);
//    }
//    this->init_level(map_name);
//}
//
//void Game::restart_player() {
//    // load save
//    std::cout << "restart" << std::endl;
//    std::string path = RESOURCE_PATH;
//    std::string buf = Levels::Level::read_file(path + SAVE_PATH);
//
//    if (!buf.empty()) {
//        // parse save if not restarting
//        if (this->menu->get_state() != Managers::restart) {
//            if(this->menu->get_state() == Managers::loading) {
//                this->parse_save(buf);
//
//            }
//        } else if (this->menu->get_state() == Managers::restart) {
//                // restart at beginning of level
//                if (this->jaime->get_state() == Entities::dead) {
//                    this->jaime->restart(
//                            this->start_location.get_x(),
//                            this->start_location.get_y(),
//                            this->jaime->get_coins(),
//                            this->jaime->get_life_number(),
//                            Entities::idle);
//
//                    std::string map_name = this->level->get_name();
//                    // restart level
//                    this->init_level(map_name);
//                    // restart time
//                    this->total_time = TIME;
//                }
//        }
//    } else {
//        if (this->jaime->get_state() == Entities::dead) {
//            this->jaime->restart(
//                    this->start_location.get_x(),
//                    this->start_location.get_y(),
//                    this->jaime->get_coins(),
//                    this->jaime->get_life_number(),
//                    Entities::idle);
//
//            std::string map_name = this->level->get_name();
//            // restart level
//            this->init_level(map_name);
//            // restart time
//            this->total_time = TIME;
//        }
//    }
//}

void Game::update() {
    this->handle_events();
    this->count_down();
    this->jaime->update();
    this->level->update();
    this->handle_resets();
    this->handle_collision();
}

void Game::render() {
    // clear window each iteration
    this->graphic_manager->clear();
    // render level first
    this->level->render();
    this->graphic_manager->reset_view();
    // render objects to display information about score, time etc...
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
//
//void Game::next_map() {
//    this->init_level(PLATFORM2);
//    this->jaime->restart(
//            this->start_location.get_x(),
//            this->start_location.get_y(),
//            this->jaime->get_coins(),
//            this->jaime->get_life_number(),
//            Entities::idle);
//}