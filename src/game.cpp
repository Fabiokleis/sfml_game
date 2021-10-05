#include <iostream>
#include "game.hpp"
#include "config.h"

Game::Game() {
    // setup game
    this->init_window(1368, 768);
    this->init_textures();
    this->init_background();
    this->init_player();
};

Game::~Game() {
    delete window;
    delete player;

    for (auto &i : this->textures) {
        delete i.second;
    }
}

void Game::init_window(int width, int height) {
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), "test");

    this->window->setFramerateLimit(60);
}

void Game::init_background() {
    std::string path = RESOURCE_PATH;
    if (!this->background_tex.loadFromFile(path+"ghost_bg_large.png")) {
        std::cout << "ERROR:GAME::COULD NOT LOAD BACKGROUND TEXTURE." << std::endl;
    }

    this->background.setTexture(this->background_tex);
}

void Game::init_textures() {
}

void Game::init_player() {
    this->player = new Player();
}


void Game::game_loop() {

    while (this->window->isOpen()) {
        this->update();
        this->render();
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
         }
    }
}

void Game::render_bg() {
    this->window->draw(this->background);
}

void Game::render() {
    this->window->clear();
    this->render_bg();
    this->player->render(this->window);
    this->window->display();
}

void Game::update() {
    this->handle_events();
    this->player->update(this->window);

}

void Game::exec() {
    this->game_loop();
}
