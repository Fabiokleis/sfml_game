#include <iostream>
#include "game.hpp"

Game::Game() :
        window_server("c++ game")
{
    // setup game
    this->init_entities();
    this->init_map();
}

Game::~Game() {
    delete map;
    delete player;
    delete fps_text;
}

void Game::init_entities() {

    this->fps_text = this->window_server.create_text("fonts/free_pixel.ttf", 32,  992, 0, sf::Color::Yellow);
    this->player = this->window_server.create_player(
                    sf::Vector2f(45.0f, 80.0f),
                    sf::Vector2f(0.0f, 0.0f),
                    sf::Vector2f(512.0f, 320.0f),
                    sf::Vector2f(0.0f, 0.0f),
                    sf::Vector2u(3, 6),
                    0.1f,
                    Entities::falling,
                    std::string("player/player_sprite.png"));
}

void Game::init_map() {
    this->map = window_server.create_map();
    this->tiles = this->map->get_tiles();
    this->tilemap = this->map->get_tilemap();
    this->map_backgrounds = this->map->get_backgrounds();
}

void Game::set_fps(float fps) {
    this->fps_text->set_text(std::to_string((int)fps));
}

void Game::handle_collision() {

    // map and player collision
    for (auto& tile : this->tiles) {
        if (tile.get_collider().check_collision(this->player->get_collider(), this->player->get_velocity())) {
            this->player->on_collision();
        }
    }
}

void Game::handle_events() {
    while (this->window_server.poll_event()) {
        switch (this->window_server.get_event().type) {

            case sf::Event::Closed:
                this->window_server.get_window()->close();
                break;

            case sf::Event::KeyPressed:

                if (this->window_server.get_event().key.code == sf::Keyboard::Escape) {
                    this->window_server.get_window()->close();
                }
                if (this->window_server.get_event().key.code == sf::Keyboard::Space) {
                    this->player->set_state(Entities::jumping);
                }

                this->player->reset_clock(this->delta_time);
                break;
            case sf::Event::KeyReleased:

                if (this->window_server.get_event().key.code == sf::Keyboard::Space) {
                    this->player->set_state(Entities::falling);
                }

                break;

            default:
                break;
        }
    }
}

void Game::game_loop() {
    
    float fps;
    sf::Clock local_clock;
    sf::Time previousTime = local_clock.getElapsedTime();
    sf::Time currentTime;

    while (this->window_server.is_open()) {

        currentTime = local_clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float 
        previousTime = currentTime;

        this->delta_time = this->clock.restart().asSeconds();
        this->set_fps(fps);
        this->update();
        this->render();
    }
}

bool Game::player_out_of_window() {
    auto map_height = this->map->get_height() * this->map->get_tile_height();
    // max y
    if (this->player->get_position().y > map_height) {
        return true;
    }
    return false;
}

void Game::update_view() {
    auto vhalf = this->window_server.get_view_size() / 2;
    auto map_height = this->map->get_height() * this->map->get_tile_height();
    auto map_width = this->map->get_width() * this->map->get_tile_width();
    sf::Vector2f view_pos(this->player->get_position());

    // force view center to stay in map width, height, left and top
    if (!this->player_out_of_window()) {
        if (this->player->get_position().x + vhalf >= map_width) {
            view_pos.x = map_width - vhalf;
        } else if (this->player->get_position().x <= vhalf) {
            view_pos.x = vhalf;
        }
        if (this->player->get_position().y + vhalf >= map_height) {
            view_pos.y = map_height - vhalf;
        }
        this->window_server.set_view_center(view_pos);
    }
}

void Game::update() {
    this->handle_events();
    this->map->update();
    this->player->update();
    this->handle_collision();
    this->update_view();
}

void Game::render_map() {
    for (int i = static_cast<int>(this->map_backgrounds.size()-1); i >= 0; i--) {
        this->window_server.render(this->map_backgrounds[i].get_sprite());
    }
    for (int i = static_cast<int>(this->tilemap.size()-1); i >= 0; i--) {
        this->window_server.render(this->tilemap[i]);
    }
}

void Game::render() {
    this->window_server.clear();
    this->render_map();
    this->window_server.render(this->fps_text->get_text());
    this->window_server.render(this->player->get_sprite());
    this->window_server.set_view();
    this->window_server.get_window()->display();
}

void Game::exec() {
    this->game_loop();
}
