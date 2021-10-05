#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#pragma once
class Game {
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        void create_window(char *name, int width, int height);
        void game_loop();
        void handle_events();
        void render();
        void update();

 
    
    public:
        Game();
        ~Game();
        void exec();
};
