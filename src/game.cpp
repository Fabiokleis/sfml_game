#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>

Game::Game() {
    // Create a window
    create_window("GAME TEST", 800, 600);
};

Game::~Game() {

}

void Game::create_window(char *name, int width, int height) {
    window.create(sf::VideoMode(width, height), name);
}

void Game::game_loop() {

    // handle closing the window
    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();
        }
    }
}


void Game::exec() {
    game_loop();
}