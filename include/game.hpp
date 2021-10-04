#include <SFML/Graphics.hpp>

#pragma once
class Game {
    private:
        sf::Window window;
    
    public:
        Game();
        ~Game();
        void create_window(char *name, int width, int height);
        void game_loop();
        void exec();
};