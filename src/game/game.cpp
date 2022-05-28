#include <iostream>
#include "game.hpp"
#include <fstream>
#include "../rapidjson/document.h"

Game::Game() :
        player(), player_dead(), map(), menu_bg(), menu(), load(), load_bg(), fps_text(), delta_time(), menu_options(),
        coin_image(), coin_number(), time_text(), total_time(256), life_image(), life_text()
{
    this->window_server = new Controllers::WindowServer("c++ game");
    this->on_menu = true;
}

void Game::exec() {
    // setup game

    this->init_menu();
    this->menu_loop();

    if (this->window_server->is_open() && !this->on_menu) {

        this->init_map();
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
    delete load_bg;
    delete load;
    delete menu;
    delete window_server;
    delete coin_image;
    delete coin_number;
    delete life_image;
    delete life_text;
}

void Game::menu_loop(bool from_game, bool from_player_dead) {
    while (this->window_server->is_open() && this->on_menu) {
        if (this->load->get_on_menu()) {
            this->load->handle_events(*this->window_server);
            this->menu->set_on_submenu(this->load->get_on_menu());
            this->load->update(from_game, from_player_dead);
            this->render_settings();
        } else {
            this->on_menu = this->menu->get_on_menu();
            this->menu->handle_events(*this->window_server);
            this->load->set_on_menu(this->menu->get_on_submenu());
            this->menu->update(from_game, from_player_dead);
            this->render_menu();
        }
    }
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
    this->menu_bg = new Entities::Image(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_X, WINDOW_Y), sf::Color::Black);
    this->load_bg = new Entities::Image(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_X, WINDOW_Y), sf::Color::Black);
    this->menu = new Controllers::MainMenu(*menu_bg, sf::Vector2f(0.0f, 0.0f), this->menu_options);
    this->load = new Controllers::SubMenu(*load_bg, sf::Vector2f(0.0f, 0.0f), this->load_options);
    this->menu_entries();
}

void Game::menu_entries() {
    /*
        [1] New Game
        [2] Load Map
            [1] Resume
            [2] Map1
            [3] Map2
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
            0.0f,
            "Load Map"));
    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Credits"));
    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Exit"));

    // populate load
    this->load->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Resume"));
    this->load->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Map 1"));
    this->load->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f + 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f, "Map 2"));
}

void Game::init_entities() {

    // fps text
    this->fps_text = new Entities::Text(
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color::Yellow);

    sf::Vector2f p_pos(this->start_location.get_x(), this->start_location.get_y());
    // player
    this->player = new Entities::Player(
                    sf::Vector2f(45.0f, 80.0f),
                    sf::Vector2f(0.0f, 0.0f),
                    p_pos,
                    sf::Vector2f(0.0f, 0.0f),
                    sf::Vector2u(3, 6),
                    0.1f,
                    Entities::States::idle,
                    std::string(PLAYER_SPRITE_PATH));

    // life
    this->life_image = new Entities::Image("map/head_sprite.png");
    this->life_image->set_position(sf::Vector2f(32.0f, 32.0f));
    this->life_text = new Entities::Text(
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color(192, 192, 192)
            );

    // coins
    this->coins = this->tiles.get_coins();
    this->coin_image = new Entities::Image("map/coin.png");
    this->coin_image->set_position(sf::Vector2f(WINDOW_X - 64, this->coin_image->get_sprite().getSize().y));
    this->coin_number = new Entities::Text(
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color(192, 192, 192)
            );

    // time text
    this->time_text = new Entities::Text(
            FONT_PATH,
            48,
            0.0f,
            0.0f,
             sf::Color(192, 192, 192)
            );
}

void Game::init_map() {
    this->map = new Maps::Map("platform.json");
    this->tiles = this->map->get_tiles();
    this->locations = this->map->get_locations();
    this->walls = this->map->get_walls();
    this->platforms = this->map->get_platforms();
    this->start_location = locations.get_start(); // start position of player
    this->check_point_location = locations.get_check_point(); // check point to save game
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

void Game::handle_collision() {
    if (this->player->get_state() != Entities::dead) {
        this->handle_player_collision();
    } else {
        this->player_dead = true;
        this->menu->set_on_menu(true);
        this->on_menu = this->menu->get_on_menu();
        this->menu_loop(false, player_dead); // create a specific flag to restart game
    }
}

void Game::handle_player_collision() {
    if (this->player_out_of_window()) {
        this->player->set_state(Entities::dead);
    }
    if (this->player->get_state() != Entities::dead) {
        if (this->end_location.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), false)) {
            // verify if player collide with the end of map, to load next map

        }

        if (this->check_point_location.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), true)) {
            // verify if player collide with check point to save the game
            this->save_game();
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
                for (auto coin = this->coins.cbegin(); coin < this->coins.cend(); *coin++) {
                    // if coin id is equal tile id, then increment player score and erase from coins after testing collision
                    if (coin->get_id() == tile.get_id()) {
                        // verify collision
                        if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(),false)) {
                            this->player->on_collision(tile.get_type());
                            coin = this->coins.erase(coin);
                        }
                    }
                }
            }
            if (tile.get_type() == "spike" || tile.get_type() == "block") {
                if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(),
                                                        true)) {
                    this->player->on_collision(tile.get_type());
                }
            }
        }
    }
}

void Game::handle_events() {
    while (this->window_server->poll_event()) {
        this->player->handle_events(*this->window_server);
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
                }
                break;
            case sf::Event::KeyReleased:
                if (this->window_server->get_event().key.code == sf::Keyboard::Escape) {
                    this->player->set_state(Entities::falling);
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
    }
}

void Game::save_game() {
    std::cout << "Saving the game on check point!" << std::endl;

    std::string path = RESOURCE_PATH;
    path += "player/save_state.json";
    int coin = this->player->get_coins();
    int life= this->player->get_life_number();
    double x = this->check_point_location.get_x();
    double y = this->check_point_location.get_y();
    std::fstream save_file(path, std::ostream::out);

    if (save_file.is_open()) {
        // write a save file in json format
        save_file << "{\n"
                << "    \"coin\": " << coin << ",\n"
                << "    \"life\": " << life << ",\n"
                << "    \"x\": " << x << ",\n"
                << "    \"y\": " << y << ",\n"
                << "}";
        save_file.close();
    } else {
        std::cout << "ERROR::SAVE_FILE:: COULD NOT OPEN FILE." << std::endl;
    }
}

void Game::load_save() {
    // load save by a json file
    std::string path = RESOURCE_PATH;
    path += "player/save_state.json";
    rapidjson::Document save_file;
    std::cout << path << "\n";
    std::ostringstream buf;
    std::ifstream input(path.c_str());
    buf << input.rdbuf();
    std::cout << buf.str();
    save_file.Parse(buf.str().c_str());
}


void Game::update() {
    this->handle_events();
    this->count_down();
    this->player->update();
    this->handle_collision();
}

void Game::render_menu() {
    this->window_server->clear();
    this->window_server->reset_view();
    this->window_server->render(this->menu->get_sprite());
    for (auto &option : this->menu_options) {
        this->window_server->render(option.get_text());
    }
    this->window_server->display();
}

void Game::render_settings() {
    this->window_server->clear();
    this->window_server->reset_view();
    this->window_server->render(this->load->get_sprite());
    for (auto &option : this->load_options) {
        this->window_server->render(option.get_text());
    }
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
        this->window_server->render(plat.get_rect_sprite());
    }
    for (auto &wall : this->walls.get_walls()) {
        this->window_server->render(wall.get_rect_sprite());
    }
    for (auto &tile : this->tiles.get_tiles()) {
        this->window_server->render(tile.get_rect_sprite());
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
