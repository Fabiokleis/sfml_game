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
    this->tiles = this->map->get_tiles();
}

void Game::init_player() {
    this->player = new Player(96.f, 100.f);
}


void Game::handle_collision() {

    // window global collision
    if (this->player->get_position().x < 0) {
        this->player->set_position(0.0f, this->player->get_position().y);
    }
    if (this->player->get_position().y < 0) {
        this->player->set_position(this->player->get_position().x, 0.0f);
    }
    if (this->player->get_position().x + this->player->get_bounds().width > this->window->getSize().x) {
        this->player->set_position(this->window->getSize().x - this->player->get_bounds().width, this->player->get_position().y);
    }
    if (this->player->get_position().y + this->player->get_bounds().height > this->window->getSize().y) {
        this->player->set_position(this->player->get_position().x, this->window->getSize().y - this->player->get_bounds().height);
    }

    // map and player collision
    for (auto& tile : this->tiles) {
        tile.check_collision(this->player->get_body(), 0.0f);
    }
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
    
    float fps;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    while (this->window->isOpen()) {
        this->update();
        this->render();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float 
        previousTime = currentTime;

        std::cout << "fps: " << floor(fps) << std::endl;

    }
}

void Game::update() {
    this->handle_events();
    this->map->update();
    this->player->update();
    this->handle_collision();
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
