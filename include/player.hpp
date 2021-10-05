#include <SFML/Graphics.hpp>
#include "config.h"

#pragma once
class Player {
    private:
        sf::Sprite sprite;
        sf::Texture texture;

        float movement_speed;

        void init_texture();


    public:
        Player();
        ~Player();
        void update(sf::RenderTarget* target);
        void update_window_collision(sf::RenderTarget* target);
        void update_input();
        void move(const float dirX, const float dirY);
        void render(sf::RenderTarget* target);
};
