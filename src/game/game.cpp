#include <iostream>
#include "game.hpp"
#include <fstream>

Game::Game() :
        player(), map(), menu_bg(), menu(), settings(), settings_bg(), fps_text(), delta_time(), menu_options(),
        coin_image(), coin_number(), time_text(), total_time(TIME), life_image(), life_text(), score_text(),
        menu_title(), about(), showkb(), credit()
{
    this->window_server = new Controllers::WindowServer("c++ game");
    this->on_menu = true;
}

void Game::exec() {
    // setup game

    this->init_menu();
    this->init_score();
    this->menu_loop();

    if (this->window_server->is_open() && !this->on_menu) {

        // only load saved map if menu load save is selected
        if (this->menu->get_saved() && this->menu->get_state() != Controllers::restart) {
            // verify if saved map is first or second
            if (this->verify_map()) {
                this->init_map(PLATFORM1);
            } else {
                this->init_map(PLATFORM2);
            }
        } else {
            // default first map when not save found and not from load
            this->init_map(PLATFORM1);
        }
        this->init_entities();
        // to init timer after load map and any other entity
        sf::Clock timer;
        this->game_loop(timer);
    }
}

Game::~Game() {
    delete fps_text;
    delete player;
    delete map;
    delete menu_bg;
    delete settings_bg;
    delete settings;
    delete menu;
    delete window_server;
    delete coin_image;
    delete coin_number;
    delete life_image;
    delete life_text;
    delete score_text;
    delete menu_title;
}

void Game::menu_loop(bool from_game, bool from_player_dead) {
    while (this->window_server->is_open() && this->on_menu) {
        if (this->settings->get_on_menu()) {
            this->settings->handle_events(*this->window_server);
            this->menu->set_on_submenu(this->settings->get_on_menu());
            this->settings->update(from_game, from_player_dead);
            this->render_settings();
        } else {
            std::cout << "state: " << this->menu->get_state() << std::endl;
            this->on_menu = this->menu->get_on_menu();
            this->menu->handle_events(*this->window_server);
            this->settings->set_on_menu(this->menu->get_on_submenu());
            this->menu->update(from_game, from_player_dead);
            this->render_menu();
        }
    }

}

bool Game::verify_map() {
    std::string path = RESOURCE_PATH;
    std::string buf = Maps::Map::read_file(path+SAVE_PATH);
    rapidjson::Document saved_file;
    saved_file.Parse(buf.c_str());
    std::string map_name = saved_file["map_name"].GetString();
    if (map_name == PLATFORM1) {
        return true;
    }
    return false;
}

void Game::game_loop(sf::Clock timer) {
    float fps;
    sf::Clock local_clock;
    sf::Time previousTime = local_clock.getElapsedTime();
    sf::Time currentTime;
    this->clock.restart();
    while (this->window_server->is_open() && !this->on_menu) {
        float aux_time = timer.getElapsedTime().asSeconds();
        if (aux_time > 1 && this->total_time >= 0) {
            this->set_time();
            timer.restart();
        }

        currentTime = local_clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        previousTime = currentTime;

        this->delta_time = this->clock.restart().asSeconds();
        this->player->reset_clock(delta_time);
        this->set_score(this->player->get_coins(), this->player->get_life_number());
        this->set_fps(fps);

        this->update();
        this->render();
    }
}

void Game::count_down() {
    if (this->total_time == -1) {
        this->player->set_state(Entities::dead);
    }
}

void Game::init_menu() {
    // game menu
    this->menu_bg = new Entities::Image(0, 0, WINDOW_X, WINDOW_Y, sf::Color::Black);
    this->settings_bg = new Entities::Image(0.0f, 0.0f, WINDOW_X, WINDOW_Y, sf::Color::Black);
    this->menu_title = new Entities::Text(
            FONT_PATH,
            80,
            WINDOW_X / 2 - 240.0f,
            100,
            sf::Color::White,
            1 << 1,
            sf::Color(95, 0, 160),
            0.0f,
            "Jaime Adventures");

    this->menu_title->set_attr(sf::Color::White, sf::Color(95, 0, 160), 3.0f, 1 << 1);

    this->menu = new Controllers::MainMenu(*menu_title, *menu_bg, 0, 0, this->menu_options);
    this->settings = new Controllers::SubMenu(*menu_title, *settings_bg, 0, 0, this->settings_options);

    // submenu actions
    this->about = new Entities::Text(
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

    // credits
    this->credit = new Entities::Text(
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

    // load a keyboard mapping explain
    this->showkb = new Entities::Image(KEYBOARD);


    this->menu_entries();
}


void Game::init_score() {
    // score text on window
    if (this->menu->get_saved()) {
        std::string path = RESOURCE_PATH;
        path += SAVE_PATH;
        std::string buf = Maps::Map::read_file(path);
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


        this->score_text = new Entities::Text(
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

void Game::menu_entries() {
    /*
        [1] New Game
        [2] Load save
            [1] Resume
            [2] About
            [3] Show Controls
        [3] Credits
        [4] Exit
    */

    // populate menu
    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 128.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "New Game"));


    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Load save"));


    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Settings"));
    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Credits"));
    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 128.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Exit"));

    // populate load
    this->settings->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Resume"));
    this->settings->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "About"));
    this->settings->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Show Controls"));
}

void Game::init_entities() {

    // fps text
    this->fps_text = new Entities::Text(
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color::Yellow);


    // create a new player with save
    if (this->menu->get_load()) {
        std::string path = RESOURCE_PATH;
        std::string buf = Maps::Map::read_file(path+SAVE_PATH);
        this->parse_save(buf);
        std::string map_name = this->map->get_name();
        // restart map
        this->init_map(map_name);
        // restart time
        this->total_time = TIME;

    } else {

        // create a new player without save
        this->player = new Entities::Player(
                this->start_location.get_x(), this->start_location.get_y(), 45, 80, 0, 0, 0, 0, 0, 5,
                sf::Vector2u(3, 6), 0.1f, Entities::idle, PLAYER_SPRITE_PATH);
    }

    // life
    this->life_image = new Entities::Image("map/head_sprite.png");
    this->life_image->set_position(32.0f, 32.0f);
    this->life_text = new Entities::Text(
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
    this->coin_image = new Entities::Image("map/coin.png");
    this->coin_image->set_position(WINDOW_X - 64, this->coin_image->get_sprite().getSize().y);

    this->coin_number = new Entities::Text(
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
    this->time_text = new Entities::Text(
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

void Game::init_map(std::string map_name) {
    this->map = new Maps::Map(map_name);
    this->tiles = this->map->get_tiles();
    this->coins = this->tiles.get_coins();
    this->locations = this->map->get_locations();
    this->walls = this->map->get_walls();
    this->platforms = this->map->get_platforms();
    this->start_location = locations.get_start(); // start position of player
    this->check_point_locations = locations.get_check_points(); // check points to save game
    this->end_location = locations.get_end(); // end of the map, defined to load other map
    this->tilemap = this->map->get_tilemap();
    this->map_backgrounds = this->map->get_backgrounds();
}

void Game::set_fps(float fps) {
    sf::Vector2f pos(WINDOW_X, 8.0f);
    pos.x -= 16;
    this->fps_text->set_position(pos);
    this->fps_text->set_text(std::to_string((int)fps));
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
        this->player->set_state(Entities::dead);
        this->player->update_life_number();
    }

    // verify if player dead and restart
    if (this->player->get_state() == Entities::dead) {
        this->menu->set_on_menu(true);
        this->on_menu = this->menu->get_on_menu();
        this->menu_loop(false, true); // create a specific flag to restart game
        // out of the menu, after select a restart option
        this->restart_player();
        this->on_menu = this->menu->get_on_menu();

    }
}


void Game::handle_collision() {

    this->handle_player_collision();
}

void Game::handle_player_collision() {

    if (this->end_location.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), false)) {
        // verify if player collide with the end of map, to load next map
        this->next_map();
    }
    for (auto &check_point : this->check_point_locations) {
        if (check_point.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), false)) {
            // verify if player collide with check point to save the game
            this->save_game(check_point);
        }
    }

    // platform and player collision
    for (auto &platform: this->platforms.get_platforms()) {
        if (platform.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(),
                                                    true)) {
            this->player->on_collision(platform.get_type());
        }
    }
    // walls and player collision
    for (auto &wall: this->walls.get_walls()) {
        if (wall.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), true)) {
            this->player->on_collision(wall.get_type());
        }
    }
    // tiles and player collision, set a different collision by type
    for (auto &tile: this->tiles.get_tiles()) {

        if (tile.get_type() == "coin" && !this->coins.empty()) {
            if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(),false)) {
                for (auto coin = this->coins.cbegin(); coin < this->coins.cend(); *coin++) {
                    // if coin id is equal tile id, then increment player score and erase from coins after testing collision
                    if (coin->get_id() == tile.get_id()) {
                        coin = this->coins.erase(coin);
                        this->player->on_collision(tile.get_type());
                    }
                }
            }
        }

        if (tile.get_type() == "spike" ) {
            if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(),
                                                    true)) {
                if (this->player->get_state() != Entities::dead) {
                    this->player->on_collision(tile.get_type());
                }
            }
        }
        if (tile.get_type() == "block") {
            if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(),
                                                    true)) {
                this->player->on_collision(tile.get_type());
            }
        }
    }
}

void Game::handle_events() {
    while (this->window_server->poll_event()) {

        if (this->player->get_state() != Entities::dead) {
            this->player->handle_events(*this->window_server);
        }


        switch (this->window_server->get_event().type) {

            case sf::Event::Closed:
                this->window_server->close();
                break;

            case sf::Event::Resized:
                this->window_server->resize_view(
                        sf::Vector2f(this->window_server->get_event().size.width,
                        this->window_server->get_event().size.height));
                break;
            case sf::Event::KeyPressed:
                // return to menu, automatically pause game loop
                if (this->window_server->get_event().key.code == sf::Keyboard::Escape) {
                    this->menu->set_on_menu(true);
                    this->on_menu = this->menu->get_on_menu();
                    this->menu_loop(true);
                    this->on_menu = this->menu->get_on_menu();
                    this->restart_player();
                }
                break;
            default:
                break;
        }
    }
}

bool Game::player_out_of_window() {
    auto map_height = this->map->get_height() * this->map->get_tile_height();
    auto map_width = this->map->get_width() * this->map->get_tile_width();

    // force player to stay in bottom/left/right position on map
    if (this->player->get_position().y > map_height || this->player->get_position().x > map_width || this->player->get_position().x < 0.0f) {
        return true;
    }
    return false;
}

void Game::update_player_view() {
    auto vhalfsize = this->window_server->get_view_size() / 2.0f;
    auto map_height = this->map->get_height() * this->map->get_tile_height();
    auto map_width = this->map->get_width() * this->map->get_tile_width();
    sf::Vector2f view_pos(this->player->get_position());

    // force view to stay in map width, height, left and top
    if (!this->player_out_of_window()) {
        if (this->player->get_position().x + vhalfsize.x >= map_width) {
            view_pos.x = map_width - vhalfsize.x;
        } else if (this->player->get_position().x <= vhalfsize.x) {
            view_pos.x = vhalfsize.x;
        }
        if (this->player->get_position().y + vhalfsize.y >= map_height) {
            view_pos.y = map_height - vhalfsize.y;
        }
        this->window_server->set_view(sf::View(view_pos, this->window_server->get_window_size()));
    } else {
        this->window_server->reset_view();
    }
}

void Game::save_game(Maps::Object current_check_point) {
    std::cout << "Saving the game on check point!" << std::endl;

    std::string path = RESOURCE_PATH;
    int coin = this->player->get_coins();
    int life = this->player->get_life_number();
    double x = current_check_point.get_x();
    double y = current_check_point.get_y();
    std::string map_name = this->map->get_name();
    std::fstream save_file(path+SAVE_PATH, std::ostream::out);

    if (save_file.is_open()) {
        // write a save file in json format
        save_file << "{\n"
                << "    \"time\": " << this->total_time << ",\n"
                << "    \"map_name\": " <<  "\"" << map_name << "\",\n"
                << "    \"coin\": " << coin << ",\n"
                << "    \"life\": " << life << ",\n"
                << "    \"x\": " << x << ",\n"
                << "    \"y\": " << y << "\n"
                << "}";
        save_file.close();
    } else {
        std::cout << "ERROR::SAVE_FILE:: COULD NOT OPEN FILE." << std::endl;
    }
}


void Game::parse_save(const std::string& buf) {
    // parse json saved file to be a new instance of player and map
    rapidjson::Document saved_file;
    saved_file.Parse(buf.c_str());

    int coin = saved_file["coin"].GetInt();
    int life = saved_file["life"].GetInt();
    double x = saved_file["x"].GetDouble();
    double y = saved_file["y"].GetDouble();
    int time = saved_file["time"].GetInt();
    this->total_time = time;
    std::string map_name = saved_file["map_name"].GetString();

    if (this->player) {
        this->player->restart(x, y, coin, life, Entities::idle);
    } else {
        this->player = new Entities::Player(
                x, y, 45, 80, 0, 0, 0, 0, coin, life,
                sf::Vector2u(3, 6), 0.1f, Entities::idle, PLAYER_SPRITE_PATH);
    }
    this->init_map(map_name);

}
void Game::restart_player() {
    // load save
    std::cout << "restart" << std::endl;
    std::string path = RESOURCE_PATH;
    std::string buf = Maps::Map::read_file(path+SAVE_PATH);

    if (!buf.empty()) {
        // parse save if not restarting
        if (this->menu->get_state() != Controllers::restart) {
            if(this->menu->get_state() == Controllers::loading) {
                this->parse_save(buf);

            }
        } else if (this->menu->get_state() == Controllers::restart) {
                // restart at beginning of map
                if (this->player->get_state() == Entities::dead) {
                    this->player->restart(
                            this->start_location.get_x(),
                            this->start_location.get_y(),
                            this->player->get_coins(),
                            this->player->get_life_number(),
                            Entities::idle);

                    std::string map_name = this->map->get_name();
                    // restart map
                    this->init_map(map_name);
                    // restart time
                    this->total_time = TIME;
                }
        }
    } else {
        if (this->player->get_state() == Entities::dead) {
            this->player->restart(
                    this->start_location.get_x(),
                    this->start_location.get_y(),
                    this->player->get_coins(),
                    this->player->get_life_number(),
                    Entities::idle);

            std::string map_name = this->map->get_name();
            // restart map
            this->init_map(map_name);
            // restart time
            this->total_time = TIME;
        }
    }
}

void Game::update() {
    this->handle_events();
    this->count_down();
    this->player->update();
    this->handle_resets();
    this->handle_collision();
}

void Game::render_menu() {
    this->window_server->clear();
    this->window_server->reset_view();
    this->window_server->render(this->menu->get_sprite());
    this->window_server->reset_view();
    this->window_server->render(this->menu_title->get_text());
    if (this->menu->get_state() == Controllers::credits) {
        this->window_server->reset_view();
        this->window_server->render(this->credit->get_text());
        this->window_server->reset_view();
    } else {
        for (auto &option: this->menu_options) {
            this->window_server->render(option.get_text());
        }
        if (this->menu->get_saved()) {
            this->window_server->reset_view();
            this->window_server->render(this->score_text->get_text());

        }
    }
    this->window_server->display();
}

void Game::render_settings() {
    this->window_server->clear();
    this->window_server->reset_view();
    this->window_server->render(this->settings->get_sprite());
    this->window_server->reset_view();

    if (this->settings->get_state() == Controllers::showkb) {
        this->window_server->render(this->showkb->get_sprite());
    } else if (this->settings->get_state() == Controllers::about) {
        this->window_server->render(this->about->get_text());
    } else {
        for (auto &option: this->settings_options) {
            this->window_server->render(option.get_text());
        }
    }
    this->window_server->render(this->menu_title->get_text());
    this->window_server->reset_view();
    this->window_server->display();
}

void Game::render_map() {
    for (int i = static_cast<int>(this->map_backgrounds.size()-1); i >= 0; i--) {
        this->window_server->render(this->map_backgrounds[i].get_sprite());
    }
    for (int i = static_cast<int>(this->tilemap.size()-1); i >= 0; i--) {
        this->window_server->render(this->tilemap[i]);
    }
    for (auto &plat : this->platforms.get_platforms()) {
        this->window_server->render(plat.get_sprite());
    }
    for (auto &wall : this->walls.get_walls()) {
        this->window_server->render(wall.get_sprite());
    }
    for (auto &tile : this->tiles.get_tiles()) {
        this->window_server->render(tile.get_sprite());
    }
    for (auto &coin : this->coins) {
        this->window_server->render(coin.get_sprite());
    }
}

void Game::render() {
    // clear window each iteration
    this->window_server->clear();
    // render map first
    this->render_map();
    this->window_server->reset_view();

    // render objects to display information about score, time etc...
    this->window_server->render(this->coin_number->get_text());
    this->window_server->reset_view();
    this->window_server->render(this->coin_image->get_sprite());
    this->window_server->reset_view();
    this->window_server->render(this->fps_text->get_text());
    this->window_server->reset_view();
    this->window_server->render(this->time_text->get_text());
    this->window_server->reset_view();
    this->window_server->render(this->life_text->get_text());
    this->window_server->reset_view();
    this->window_server->render(this->life_image->get_sprite());

    // render player sprite, but he needs a different view size
    this->update_player_view();
    this->window_server->render(this->player->get_sprite());

    // finally, display everything
    this->window_server->display();
}

void Game::next_map() {
    this->init_map(PLATFORM2);
    this->player->restart(
            this->start_location.get_x(),
            this->start_location.get_y(),
            this->player->get_coins(),
            this->player->get_life_number(),
            Entities::idle);
}