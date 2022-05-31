#include <iostream>
#include "game.hpp"
#include <fstream>

Game::Game() :
        player(), phase(), menu(), settings(), delta_time(), coin_image(), coin_number(),
        time_text(), total_time(TIME), life_image(), life_text(), score_text(), on_menu()
{
    this->graphic_manager = new Managers::GraphicManager("c++ game");

}

void Game::exec() {
    // setup game

    this->init_menu();
    this->init_score();
    this->menu_loop();

    if (this->graphic_manager->is_open() && !this->on_menu) {

        // only load saved phase if menu load save is selected
        if (this->menu->get_saved() && this->menu->get_state() != Managers::restart) {
            // verify if saved phase is first or second
            if (this->verify_map()) {
                this->init_phase(PLATFORM1);
            } else {
                this->init_phase(PLATFORM2);
            }
        } else {
            // default first phase when not save found and not from load
            this->init_phase(PLATFORM1);
        }
        this->init_entities();
        // to init timer after load phase and any other entity
        sf::Clock timer;
        this->game_loop(timer);
    }
}

Game::~Game() {
    delete player;
    delete phase;
    delete settings;
    delete menu;
    delete graphic_manager;
    delete coin_image;
    delete coin_number;
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
            this->render_settings();
        } else {
            std::cout << "state: " << this->menu->get_state() << std::endl;
            this->on_menu = this->menu->get_on_menu();
            this->menu->handle_events(*this->graphic_manager);
            this->settings->set_on_menu(this->menu->get_on_submenu());
            this->menu->update(from_game, from_player_dead);
            this->render_menu();
        }
    }

}

bool Game::verify_map() {
    std::string path = RESOURCE_PATH;
    std::string buf = Levels::Level::read_file(path + SAVE_PATH);
    rapidjson::Document saved_file;
    saved_file.Parse(buf.c_str());
    std::string map_name = saved_file["map_name"].GetString();
    if (map_name == PLATFORM1) {
        return true;
    }
    return false;
}

void Game::game_loop(sf::Clock timer) {
    this->clock.restart();
    while (this->graphic_manager->is_open() && !this->on_menu) {
        float aux_time = timer.getElapsedTime().asSeconds();
        if (aux_time > 1 && this->total_time >= 0) {
            this->set_time();
            timer.restart();
        }

        this->delta_time = this->clock.restart().asSeconds();
        this->player->reset_clock(delta_time);
        this->set_score(this->player->get_coins(), this->player->get_life_number());

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
    this->menu = new Managers::MainMenu(0, 0);
    this->settings = new Managers::SubMenu(0, 0);
}


void Game::init_score() {
    // score text on window
    if (this->menu->get_saved()) {
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

void Game::init_entities() {

    // create a new player with save
    if (this->menu->get_load()) {
        std::string path = RESOURCE_PATH;
        std::string buf = Levels::Level::read_file(path + SAVE_PATH);
        this->parse_save(buf);
        std::string map_name = this->phase->get_name();
        // restart phase
        this->init_phase(map_name);
        // restart time
        this->total_time = TIME;

    } else {

        // create a new player without save
        this->player = new Entities::Player(
                *this->graphic_manager,
                this->start_location.get_x(),
                this->start_location.get_y(),
                45, 80, 0, 0, 0, 5, sf::Vector2u(3, 6), 0.1f,
                Entities::idle,
                PLAYER_SPRITE_PATH);
    }

    // life
    this->life_image = new Entities::Image(*this->graphic_manager, HEAD_SPRITE);
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
    this->coin_image = new Entities::Image(*this->graphic_manager, COIN_PATH);
    this->coin_image->set_position(WINDOW_X - 64, 32.0f);
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

void Game::init_phase(std::string map_name) {
    this->phase = new Levels::Level(map_name);
    this->tiles = this->phase->get_tiles();
    this->coins = this->tiles.get_coins();
    this->locations = this->phase->get_locations();
    this->walls = this->phase->get_walls();
    this->platforms = this->phase->get_platforms();
    this->start_location = locations.get_start(); // start position of player
    this->check_point_locations = locations.get_check_points(); // check points to save game
    this->end_location = locations.get_end(); // end of the phase, defined to load other phase
    this->tilemap = this->phase->get_tilemap();
    this->map_backgrounds = this->phase->get_backgrounds();
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
        // verify if player collide with the end of phase, to load next phase
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
    while (this->graphic_manager->poll_event()) {

        if (this->player->get_state() != Entities::dead) {
            this->player->handle_events(this->graphic_manager->get_event());
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
                    this->restart_player();
                }
                break;
            default:
                break;
        }
    }
}

bool Game::player_out_of_window() {
    auto map_height = this->phase->get_height() * this->phase->get_tile_height();
    auto map_width = this->phase->get_width() * this->phase->get_tile_width();

    // force player to stay in bottom/left/right position on phase
    if (this->player->get_position().y > map_height || this->player->get_position().x > map_width || this->player->get_position().x < 0.0f) {
        return true;
    }
    return false;
}

void Game::update_player_view() {
    auto vhalfsize = this->graphic_manager->get_view_size() / 2.0f;
    auto map_height = this->phase->get_height() * this->phase->get_tile_height();
    auto map_width = this->phase->get_width() * this->phase->get_tile_width();
    sf::Vector2f view_pos(this->player->get_position());

    // force view to stay in phase width, height, left and top
    if (!this->player_out_of_window()) {
        if (this->player->get_position().x + vhalfsize.x >= map_width) {
            view_pos.x = map_width - vhalfsize.x;
        } else if (this->player->get_position().x <= vhalfsize.x) {
            view_pos.x = vhalfsize.x;
        }
        if (this->player->get_position().y + vhalfsize.y >= map_height) {
            view_pos.y = map_height - vhalfsize.y;
        }
        this->graphic_manager->set_view(sf::View(view_pos, this->graphic_manager->get_window_size()));
    } else {
        this->graphic_manager->reset_view();
    }
}

void Game::save_game(const Levels::Object& current_check_point) {

    std::string path = RESOURCE_PATH;
    int coin = this->player->get_coins();
    int life = this->player->get_life_number();
    double x = current_check_point.get_x();
    double y = current_check_point.get_y();
    std::string map_name = this->phase->get_name();
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
    // parse json saved file to be a new instance of player and phase
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
                *this->graphic_manager,
                x, y, 45, 80,  0, 0, coin,life,
                sf::Vector2u(3, 6), 0.1f, Entities::idle, PLAYER_SPRITE_PATH);
    }
    this->init_phase(map_name);
}

void Game::restart_player() {
    // load save
    std::cout << "restart" << std::endl;
    std::string path = RESOURCE_PATH;
    std::string buf = Levels::Level::read_file(path + SAVE_PATH);

    if (!buf.empty()) {
        // parse save if not restarting
        if (this->menu->get_state() != Managers::restart) {
            if(this->menu->get_state() == Managers::loading) {
                this->parse_save(buf);

            }
        } else if (this->menu->get_state() == Managers::restart) {
                // restart at beginning of phase
                if (this->player->get_state() == Entities::dead) {
                    this->player->restart(
                            this->start_location.get_x(),
                            this->start_location.get_y(),
                            this->player->get_coins(),
                            this->player->get_life_number(),
                            Entities::idle);

                    std::string map_name = this->phase->get_name();
                    // restart phase
                    this->init_phase(map_name);
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

            std::string map_name = this->phase->get_name();
            // restart phase
            this->init_phase(map_name);
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
    this->graphic_manager->clear();
    this->graphic_manager->reset_view();
    this->graphic_manager->render(this->menu->get_sprite());
    this->graphic_manager->reset_view();

    if (this->menu->get_state() == Managers::credits) {
        this->graphic_manager->reset_view();
        this->graphic_manager->render(this->menu->show_credit().get_text());
        this->graphic_manager->reset_view();
    } else {
        for (auto &option: this->menu->get_options()) {
            this->graphic_manager->render(option->get_text());
        }
        if (this->menu->get_saved()) {
            this->graphic_manager->reset_view();
            this->graphic_manager->render(this->score_text->get_text());

        }
    }
    this->graphic_manager->render(this->menu->get_title().get_text());
    this->graphic_manager->display();
}

void Game::render_settings() {
    this->graphic_manager->clear();
    this->graphic_manager->reset_view();
    this->graphic_manager->render(this->settings->get_sprite());
    this->graphic_manager->reset_view();

    if (this->settings->get_state() == Managers::showkb) {
        this->graphic_manager->render(this->settings->show_kb().get_sprite());
    } else if (this->settings->get_state() == Managers::about) {
        this->graphic_manager->render(this->settings->show_about().get_text());
    } else {
        for (auto &option: this->settings->get_options()) {
            this->graphic_manager->render(option->get_text());
        }
    }
    this->graphic_manager->render(this->menu->get_title().get_text());
    this->graphic_manager->reset_view();
    this->graphic_manager->display();
}

void Game::render_phase() {
    for (int i = static_cast<int>(this->map_backgrounds.size()-1); i >= 0; i--) {
        this->graphic_manager->render(this->map_backgrounds[i].get_sprite());
    }
    for (int i = static_cast<int>(this->tilemap.size()-1); i >= 0; i--) {
        this->graphic_manager->render(this->tilemap[i]);
    }
    for (auto &plat : this->platforms.get_platforms()) {
        this->graphic_manager->render(plat.get_sprite());
    }
    for (auto &wall : this->walls.get_walls()) {
        this->graphic_manager->render(wall.get_sprite());
    }
    for (auto &tile : this->tiles.get_tiles()) {
        this->graphic_manager->render(tile.get_sprite());
    }
    for (auto &coin : this->coins) {
        this->graphic_manager->render(coin.get_sprite());
    }
}

void Game::render() {
    // clear window each iteration
    this->graphic_manager->clear();
    // render phase first
    this->render_phase();
    this->graphic_manager->reset_view();

    // render objects to display information about score, time etc...
    this->graphic_manager->render(this->coin_number->get_text());
    this->graphic_manager->reset_view();
    this->coin_image->render();
    this->graphic_manager->reset_view();
    this->graphic_manager->render(this->time_text->get_text());
    this->graphic_manager->reset_view();
    this->graphic_manager->render(this->life_text->get_text());
    this->graphic_manager->reset_view();
    this->life_image->render();

    // render player sprite, but he needs a different view size
    this->update_player_view();
    this->player->render();

    // finally, display everything
    this->graphic_manager->display();
}

void Game::next_map() {
    this->init_phase(PLATFORM2);
    this->player->restart(
            this->start_location.get_x(),
            this->start_location.get_y(),
            this->player->get_coins(),
            this->player->get_life_number(),
            Entities::idle);
}