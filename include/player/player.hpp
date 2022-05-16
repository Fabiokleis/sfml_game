#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include "config.h"
#include "animation.hpp"
#include "collider.hpp"

enum State {
    jumping = 0,
    right,
    left,
    falling,
    ground,
};

class Player {
    private:
        sf::IntRect shape;
        sf::RectangleShape sprite;
        sf::Texture texture;
        sf::Vector2f velocity;
        sf::Vector2f size;
        Animation* player_animation{};
        State state;

        bool can_jump;
        float jump_height{};
        float acceleration{};
        float gravity{};
        float drag{};
        float velocity_max{};
        float velocity_min{};
        float velocity_max_y{};
        float delta_time{};


    public:
        Player(float x, float y);
        ~Player();
        Collider get_collider();
        sf::Vector2f& get_velocity();

        void init_texture(float x, float y);
        void init_physics();
        void update();
        void update_input();
        void update_physics();
        void update_animation();
        void reset_clock(float dt);
        void on_collision();
        void move(float dir_x, float dir_y);
        void render(sf::RenderTarget* target);
};
