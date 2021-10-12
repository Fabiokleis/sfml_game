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

    this->window = new sf::RenderWindow(sf::VideoMode(800, 640), "test");

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
    this->player = new Player(0.f, 500.f);
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


    tmx::MapObjects objs = this->map->get_objs();

    // collision detect

    for (auto obj : objs) {
        sf::FloatRect shape = obj.getAABB();
        if (shape.intersects(this->player->get_bounds()) && obj.getType() == "horizontal_obj") { 

            this->player->reset_velocity_y();

            this->player->set_position(this->player->get_position().x, shape.top - 80);
        }

        if (shape.intersects(this->player->get_bounds()) && obj.getType() == "vertical_obj") {
            this->player->set_position(shape.left - 48, this->player->get_position().y);
            this->player->reset_velocity_y();
        }

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
    this->map->update();
    this->update_window_collision();
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
