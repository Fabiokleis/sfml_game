#include <iostream>
#include "game.hpp"
#include "config.h"

Game::Game() {
    // setup game
    this->init_window();
    this->init_background();
    this->init_map();
    this->init_player();
};

Game::~Game() {
    delete player;
    delete map;
    delete window;
}

void Game::init_window() {
    this->window = new sf::RenderWindow(sf::VideoMode(), "test", sf::Style::Fullscreen);

    this->window->setFramerateLimit(60);
}

void Game::init_background() {
    std::string path = RESOURCE_PATH;
    if (!this->background_tex.loadFromFile(path+"ghost_bg_large.png")) {
        std::cout << "ERROR:GAME::COULD NOT LOAD BACKGROUND TEXTURE." << std::endl;
    }

    this->background.setTexture(this->background_tex);
}

void Game::init_map() {
    const float grid = 32;
    const unsigned max_x = this->window->getSize().x/grid;
    const unsigned max_y = this->window->getSize().y/grid;
    this->map = new Map(grid, max_x, max_y);
}

void Game::init_player() {
    this->player = new Player();
}

void Game::game_loop() {

    while (this->window->isOpen()) {
        this->update_delta();
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
    this->map->render(this->window);
    this->player->render(this->window);
    this->window->display();
}

void Game::update() {
    this->handle_events();
    this->update_window_collision();
    this->player->update();

}

void Game::update_window_collision() {

    // getBounds -> returns a Vector thats contains 2 cordinates top and left, 2 properties width and height

    float left_pos =  this->player->getBounds().left;
    float top_pos = this->player->getBounds().top;
    float right_pos = this->player->getBounds().left + this->player->getBounds().width;
    float bottom_pos = this->player->getBounds().top + this->player->getBounds().height;

    if (left_pos < 0.f) {
        this->player->setPosition(0.f, top_pos);
    } else if (right_pos >= this->window->getSize().x) {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, top_pos);
    }
    if (top_pos < 0.f) {
        this->player->setPosition(left_pos, 0.f);
    } else if (bottom_pos >= this->window->getSize().y + 1.f) {
        this->player->setPosition(left_pos, this->window->getSize().y - this->player->getBounds().height);
    }

}

void Game::update_delta() {
    this->delta = this->delta_clock.getElapsedTime().asSeconds();
}

void Game::exec() {
    this->game_loop();
}
