#include <iostream>
#include "game.hpp"
#include "config.h"


Game::Game() {
    // setup game
    this->init_window();
    this->init_textures();
    this->init_map();

    this->init_player();
}

Game::~Game() {
    delete player;
    delete map;
    delete window;
}

void Game::init_window() {
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

    this->window = new sf::RenderWindow(sf::VideoMode(800, 608), "test");
    sf::View view = window->getView();
    view.setCenter(window_bounds.width/2,window_bounds.height/2);
    this->window->setFramerateLimit(60);
}

void Game::init_textures() {

    std::string path = RESOURCE_PATH;

    if (!this->background_tex.loadFromFile(path+"ghost_bg_large.png")) {
        std::cout << "ERROR:GAME::COULD NOT LOAD BACKGROUND TEXTURE." << std::endl;
    }

    this->background.setTexture(this->background_tex);
}

void Game::init_map() {
    this->map = new Map();
}

void Game::init_player() {
    this->player = new Player(0.f, 0.f);
}

void Game::handle_events() {

     while (this->window->pollEvent(event)) {
         switch (this->event.type) {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:

                if (this->event.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                if (
                    this->event.key.code == sf::Keyboard::W ||
                    this->event.key.code == sf::Keyboard::Space
                ) 
                {

                    this->player->reset_animation_timer();
                    this->player->set_current_key(JUMP, true);
                }


                break;

            case sf::Event::KeyReleased:
                
                if (
                    this->event.key.code == sf::Keyboard::A || 
                    this->event.key.code == sf::Keyboard::D ||
                    this->event.key.code == sf::Keyboard::S ||
                    this->event.key.code == sf::Keyboard::W ||
                    this->event.key.code == sf::Keyboard::Space
                )
                {
                    this->player->reset_animation_timer();
                }

                if (
                    this->event.key.code == sf::Keyboard::W ||
                    this->event.key.code == sf::Keyboard::Space
                ) 
                {

                    this->player->set_current_key(JUMP, false);
                }

                break;

            default:
                break;
        }
    }
}

void Game::render_bg() {
    this->window->draw(this->background);
}

void Game::update_window_collision() {

    // getBounds -> returns a Vector thats contains 2 cordinates top and left, 2 properties width and height

    float top_pos = this->player->get_bounds().top;
    float left_pos = this->player->get_bounds().left;
    float player_height = this->player->get_bounds().height;

    // bottom side collision
    if (top_pos + player_height > this->window->getSize().y) {
        // this->player->reset_velocity_y();
        this->player->set_position(left_pos, this->window->getSize().y - player_height);

    }

    // left side collision
    if (left_pos < 0.f) {
        // this->player->reset_velocity_y();
        this->player->set_position(0.f, floor(this->window->getSize().y - player_height));
    }
}

void Game::update_delta() {
    this->delta = this->delta_clock.getElapsedTime().asSeconds();
}

void Game::game_loop() {

    while (this->window->isOpen()) {
        this->update_delta();
        this->update();
        this->render();
    }
}

void Game::update() {
    this->handle_events();
    this->player->update();
    this->update_window_collision();
    this->map->update(this->player);
}

void Game::render() {
    this->window->clear();
    // this->render_bg();
    this->player->render(this->window);
    this->map->render(this->window);
    this->window->display();
}

void Game::exec() {
    this->game_loop();
}
