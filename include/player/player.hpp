#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.h"
#include "animation.hpp"
#include "collider.hpp"

#pragma once
class Player {
    private:
        sf::IntRect shape;
        sf::RectangleShape sprite;
        sf::Texture texture;
        sf::Vector2f velocity;
        sf::Vector2f size;
        Animation* player_animation{};

        float acceleration{};
        float gravity{};
        float drag{};
        float velocity_max{};
        float velocity_min{};
        float velocity_max_y{};
        bool on_ground{};
        bool collide{};
        float delta_time{};


    public:
        Player(float x, float y);
        ~Player();
        Collider get_collider();
        sf::Vector2f get_velocity();

        void init_texture(float x, float y);
        void init_physics();
        void update();
        void update_input();
        void update_physics();
        void update_animation();
        void reset_clock(float dt);
        void reset_velocity_y();
        void set_collide(bool flag);
        void move(float dir_x, float dir_y);
        void render(sf::RenderTarget* target);
};
