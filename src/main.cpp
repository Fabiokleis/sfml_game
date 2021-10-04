#include <SFML/Graphics.hpp>

int main() {

    // Create a window
    sf::Window window(sf::VideoMode(800, 600), "SFML GAME");


    // handle closing the window
    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}
