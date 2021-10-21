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

    this->window = new sf::RenderWindow(sf::VideoMode(1024, 640), "test");

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
    this->player = new Player(96.f, 100.f);
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
                this->player->reset_animation_timer();
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

                break;

            default:
                break;
        }
    }
}

void Game::render_bg() {
    this->window->draw(this->background);
}

void Game::game_loop() {

    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::update() {
    this->handle_events();
    this->map->update();
    this->player->update();
}

void Game::render() {
    this->window->clear();
    this->render_bg();
    this->player->render(this->window);
    this->map->render(this->window);
    this->window->display();
}

void Game::exec() {
    this->game_loop();
}
