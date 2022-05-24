#ifndef PLAYER_HPP_WHBHED8U
#define PLAYER_HPP_WHBHED8U
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include "config.h"
#include "character.hpp"
#include "animation.hpp"
#include "collider.hpp"

namespace Entities {

   
    class Player : public Character {
        private:
            bool can_jump{};
            float jump_height{};
            float acceleration{};
            float gravity{};
            float delta_time{};
            bool release_key;
    
    
        public:
            Player(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord, sf::Vector2u image_count, float switch_time, States state, const std::string& path_name);
            Player();

            ~Player();
            void set_key_release(bool flag);
            void init_physics();
            void update();
            void update_input();
            void update_physics();
            void update_animation();
            void reset_clock(float dt);
            void on_collision();
            void move(float dir_x, float dir_y) override;
    };
}
#endif /* end of include guard: PLAYER_HPP_WHBHED8U */
