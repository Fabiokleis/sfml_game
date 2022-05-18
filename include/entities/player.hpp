#ifndef PLAYER_HPP_WHBHED8U
#define PLAYER_HPP_WHBHED8U
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include "config.h"
#include "animation.hpp"
#include "collider.hpp"

namespace Entities {

    enum State {
        idle = 0,
        jumping,
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
            Controllers::Animation* player_animation{};
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
            Player(const float x, const float y);
            ~Player();
            Controllers::Collider get_collider();
            sf::Vector2f& get_velocity();
    
            void init_texture(float x, float y);
            void init_physics();
            void update();
            void update_input();
            void update_physics();
            void update_animation();
            void set_state(const State s);
            void reset_clock(float dt);
            void on_collision();
            void move(const float dir_x, const float dir_y);
            void render(sf::RenderTarget* target);
    };
}
#endif /* end of include guard: PLAYER_HPP_WHBHED8U */
