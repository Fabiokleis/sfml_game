#include <iostream>
#include "game.hpp"

Game::Game() :
    player(), map(), menu_bg(), menu(), settings(), settings_bg(), fps_text(), delta_time(), menu_options(), coin_image(), coin_number(), time_text(), total_time(256)
{
    this->window_server = new Controllers::WindowServer("c++ game");
    this->on_menu = true;
}

void Game::exec() {
    // setup game

    this->init_menu();
    this->menu_loop();

    if (this->window_server->is_open() && !this->on_menu) {
        sf::Clock timer;
        this->init_map();
        this->init_entities();
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
}

void Game::menu_loop(bool from_game) {
    while (this->window_server->is_open() && this->on_menu) {
        if (this->settings->get_on_menu()) {
            this->settings->handle_events(*this->window_server);
            this->menu->set_on_submenu(this->settings->get_on_menu());
            this->settings->update(from_game);
            this->render_settings();
        } else {
            this->on_menu = this->menu->get_on_menu();
            this->menu->handle_events(*this->window_server);
            this->settings->set_on_menu(this->menu->get_on_submenu());
            this->menu->update(from_game);
            this->render_menu();
        }
    }
}

void Game::game_loop(sf::Clock timer) {
    float fps;
    sf::Clock local_clock;
    sf::Time previousTime = local_clock.getElapsedTime();
    sf::Time currentTime;

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
        this->set_score(this->player->get_coins());
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
    this->settings_bg = new Entities::Image(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_X, WINDOW_Y), sf::Color::Black);
    this->menu = new Controllers::MainMenu(*menu_bg, sf::Vector2f(0.0f, 0.0f), this->menu_options);
    this->settings = new Controllers::SubMenu(*settings_bg, sf::Vector2f(0.0f, 0.0f), this->settings_options);
    this->menu_entries();
}

void Game::menu_entries() {
    /*
        [1] Start
        [2] Settings
            [1] Resume
            [2] Set fullscreen
            [3] Mute
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
            0.0f, "Start"));
    this->menu->populate_option(*new Entities::Text(
            FONT_PATH,
            48,
            WINDOW_X / 2.0f - 64.0f,
            WINDOW_Y / 2.0f - 64.0f,
            sf::Color::White,
            0,
            sf::Color::Transparent,
            0.0f,
            "Settings"));
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

    // populate settings
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
            0.0f, "Mute"));
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

    // coins
    this->coins = this->tiles.get_coins();
    this->coin_number = new Entities::Text(
            FONT_PATH,
            32,
            0.0f,
            0.0f,
            sf::Color(192, 192, 192)
            );
    this->coin_image = new Entities::Image("map/coin.png");
    this->coin_image->set_position(sf::Vector2f(WINDOW_X - 64, this->coin_image->get_sprite().getSize().y));


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
    this->map = new Maps::Map();
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

void Game::set_score(int coin) {
    sf::Vector2f pos(WINDOW_X, this->coin_image->get_sprite().getSize().y + 10.0f);
    pos.x -= 16;
    this->coin_number->set_position(pos);
    this->coin_number->set_text(std::to_string(coin));
}

void Game::set_time() {

    this->time_text->set_position(sf::Vector2f(WINDOW_X / 2 - 32.0f, 32.0f));
    std::string aux = std::to_string(this->total_time);
    this->time_text->set_text("Time " + aux);
    this->total_time--;
}

void Game::handle_collision() {
    // platform and player collision
    for (auto& platform : this->platforms.get_platforms()) {
        if (platform.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), true)) {
            this->player->on_collision(platform.get_type());
        }
    }
    // walls and player collision
    for (auto& wall : this->walls.get_walls()) {
        if (wall.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), true)) {
            this->player->on_collision(wall.get_type());
        }
    }
    // tiles and player collision, set a different collision by type
    for (auto& tile : this->tiles.get_tiles()) {
        if (tile.get_type() == "coin" && !this->coins.empty()) {
            if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), false)) {
                this->player->on_collision(tile.get_type());
                this->coins.erase(std::remove_if(coins.begin(), coins.end(), [&](const Entities::Coin& i) {
                    if (i.get_id() == tile.get_id()) this->player->inc_score();
                    return i.get_id() == tile.get_id();
                }), coins.end());
            }
        }
        if (tile.get_type() == "note") {
            if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), true)) {
                this->player->on_collision(tile.get_type());
            }
        }
        if (tile.get_type() == "spike") {
            if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity(), true)) {
                this->player->on_collision(tile.get_type());
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
        this->player->set_state(Entities::dead);
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
    this->window_server->render(this->settings->get_sprite());
    for (auto &option : this->settings_options) {
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
    this->window_server->clear();
    this->render_map();
    this->window_server->reset_view();
    this->window_server->render(this->coin_number->get_text());
    this->window_server->reset_view();
    this->window_server->render(this->coin_image->get_sprite());
    this->window_server->reset_view();
    this->window_server->render(this->fps_text->get_text());
    this->window_server->reset_view();
    this->window_server->render(this->time_text->get_text());
    this->update_player_view();
    this->window_server->render(this->player->get_sprite());
    this->window_server->display();
}
