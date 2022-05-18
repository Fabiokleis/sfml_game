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
            Controllers::Animation* player_animation{};
    
            bool can_jump{};
            float jump_height{};
            float acceleration{};
            float gravity{};
//            float drag{};
            float delta_time{};
    
    
        public:
            Player(float x, float y);
            ~Player();
    
            void init_physics();
            void update();
            void update_input();
            void update_physics();
            void update_animation();
            void reset_clock(float dt);
            void on_collision();
            void move(float dir_x, float dir_y) override;
            void render(sf::RenderTarget* target);
    };
}
#endif /* end of include guard: PLAYER_HPP_WHBHED8U */
