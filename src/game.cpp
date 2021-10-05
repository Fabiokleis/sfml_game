#include <iostream>
#include "game.hpp"
#include "config.h"

std::string contents_path = RESOURCE_PATH;

Game::Game() {
    // Create a window
    init_window(1368, 768);
    init_enemies();
};

Game::~Game() {
    delete window;
}

void Game::init_window(int width, int height) {
    videoMode.width = width;
    videoMode.height = height;

    window = new sf::RenderWindow(videoMode, "test");
}

void Game::init_enemies() {
    enemy.setPosition(10.f, 10.f);
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Cyan);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.f);
}

void Game::game_loop() {

    while (window->isOpen()) {
        handle_events();
        render();
        update();
    }
}

void Game::handle_events() {
     
     while (window->pollEvent(event)) {

         switch (event.type) {

            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                } 
         }
    }
}

void Game::render() {

    sf::Texture texture;
    texture.loadFromFile(contents_path+"ghost_bg_large.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0.f, 0.f);

    window->draw(sprite);
    window->draw(enemy);
    window->display();
}

void Game::update() {
    std::cout << sf::Mouse::getPosition(*window).x << " " << sf::Mouse::getPosition(*window).y << "\n";
}

void Game::exec() {
    game_loop();
}
