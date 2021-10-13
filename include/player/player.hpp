#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.h"

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_DOWN, JUMPING, FALLING};
enum KEYS_STATES {JUMP, LEFT, RIGHT, DOWN};

#pragma once
class Player {
    private:
        sf::IntRect shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f velocity;
        sf::Clock clock;


        float acceleration;
        float gravity;
        float drag;
        float velocity_max;
        float velocity_min;
        float velocity_max_y;
        short animation_state;
        short last_state;
        bool on_ground;
        bool animation_switch;
        std::map<KEYS_STATES, bool> state_key;


    public:
        Player(float x, float y);
        ~Player();

        sf::Vector2f get_position();
        sf::FloatRect get_bounds();
        bool get_animation_switch();
        void set_current_key(KEYS_STATES key, bool flag);

        void init_texture(const float x, const float y);
        void init_physics();
        void init_animations();
        void update();
        void update_input();
        void update_physics();
        void update_player_state();
        void update_animations();
        void reset_animation_timer();
        void reset_velocity_y();
        void set_position(const float x, const float y);
        void set_on_ground(bool flag);
        void move(const float dir_x, const float dir_y);
        void render(sf::RenderTarget* target);
};
