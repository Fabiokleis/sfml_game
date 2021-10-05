#include <SFML/Graphics.hpp>

#pragma once
class Game {
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::RectangleShape enemy;

        void init_window(int width, int height);
        void init_enemies();
        void game_loop();
        void handle_events();
        void render();
        void update();

 
    
    public:
        Game();
        ~Game();
        void exec();
};
