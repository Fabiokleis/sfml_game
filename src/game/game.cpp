#include <iostream>
#include "game.hpp"
#include "config.h"


Game::Game() {
    // setup game
    this->init_window();
    this->init_textures();
    this->init_font();
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

    this->window = new sf::RenderWindow(sf::VideoMode(1024, 640), "c++ game");

    this->window->setFramerateLimit(60);
}

void Game::init_textures() {

    std::string path = RESOURCE_PATH;

    if (!this->background_tex.loadFromFile(path+"ghost_bg_large.png")) {
        std::cout << "ERROR:GAME::COULD NOT LOAD BACKGROUND TEXTURE." << std::endl;
    }
    
    if (!this->font.loadFromFile(path+"fonts/free_pixel.ttf")) {
        std::cout << "ERROR:GAME::COULD NOT LOAD PIXEL FONT." << std::endl;
    }
    this->background.setTexture(this->background_tex);
}

void Game::init_map() {
    this->map = new Map();
    this->tiles = this->map->get_tiles();
}

void Game::init_player() {
    this->player = new Player(512, 320.f);
}

void Game::init_font() {
    this->text.setFont(this->font);
    this->text.setCharacterSize(30);
    this->text.setPosition(996, 0.0f);
    this->text.setFillColor(sf::Color::Yellow);
}

void Game::set_fps(float fps) {
    this->text.setString(std::to_string((int)fps));
}

void Game::handle_collision() {

    // map and player collision
    for (auto& tile : this->tiles) {
        this->player->set_collide(tile.check_collision(this->player->get_body(), this->player->get_velocity()));
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

void Game::render_text() {
    this->window->draw(this->text);
}

void Game::game_loop() {
    
    float fps;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    while (this->window->isOpen()) {

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float 
        previousTime = currentTime;
        this->set_fps(fps);
        this->update(); 
        this->render();
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
    this->render_text();
    this->window->display();
}

void Game::exec() {
    this->game_loop();
}
