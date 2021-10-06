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

        const sf::Vector2f getPosition() const;
        const sf::FloatRect getBounds() const;

        void update();
        void update_input();
        void setPosition(const float x, const float y);
        void move(const float dirX, const float dirY);
        void render(sf::RenderTarget* target);
};
