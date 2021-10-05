#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>

Game::Game() {
    // Create a window
    create_window("Game", 1368, 768);
};

Game::~Game() {
    delete window;
}

void Game::create_window(char *name, int width, int height) {
    videoMode.width = width;
    videoMode.height = height;

    window = new sf::RenderWindow(videoMode, name);
}

void Game::game_loop() {

    while (window->isOpen()) {
        handle_events();
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
    window->clear(sf::Color(0, 0, 0, 255)); // RGBA
    window->display();
}

void Game::update() {
    render();
}

void Game::exec() {
    game_loop();
}
