#include <SFML/Graphics.hpp>
#include "config.h"

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_DOWN, JUMPING, FALLING};

#pragma once
class Player {
    private:
        sf::IntRect shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Clock clock;
        sf::Vector2f velocity;
        float acceleration;
        float gravity;
        float drag;
        float velocity_max;
        float velocity_min;
        float velocity_max_y;
        short animation_state;
        bool animation_switch;


    public:
        Player(float x, float y);
        ~Player();

        sf::Vector2f getPosition();
        sf::FloatRect getBounds();
        bool get_animation_switch();

        void init_texture(const float x, const float y);
        void init_physics();
        void init_animations();
        void update();
        void update_input();
        void update_physics();
        void update_animations();
        void reset_animation_timer();
        void setPosition(const float x, const float y);
        void move(const float dir_x, const float dir_y);
        void render(sf::RenderTarget* target);
};
