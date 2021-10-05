#include <SFML/Graphics.hpp>
#include "config.h"

#pragma once
class Player {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        void init_texture();


    public:
        Player();
        ~Player();
        void update();
        void render(sf::RenderTarget& target);
};
