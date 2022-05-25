#ifndef CHARACTER_HPP_RMVC7YT5
#define CHARACTER_HPP_RMVC7YT5
#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.hpp"
#include "collider.hpp"
#include "animation.hpp"
#include "config.h"

namespace Entities {

    enum CollideStates {
        top = 0,
        right,
        left,
        ground,
    };

    enum States {
        idle = 0,
        walking_right,
        walking_left,
        down,
        jumping,
        falling,
        dead,
    };

    class Character : public Entity {
        private:
            Controllers::Animation *animation{};

        protected:
            sf::IntRect shape;
            sf::Vector2f velocity;
            sf::Texture texture;
            std::string path_name;
            sf::Vector2u image_count;
            float switch_time{};
            CollideStates collide_state;
            States state;
            States last_state;
            bool colliding;

        public:
            Character(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord,
                      sf::Vector2u image_count, float switch_time, States state, std::string path_name);

            Character();
            virtual ~Character();
            void init_texture();
            sf::Vector2f& get_velocity();
            Controllers::Collider get_collider();
            Controllers::Animation& get_animation();
            States get_state();
            void set_last_state(States s);
            void set_state(States s);
            void set_collide_state(CollideStates s);
            void set_colliding(bool flag);
            CollideStates get_collide_state();
            void set_rect(sf::IntRect rect);
            virtual void move(float dir_x, float dir_y) = 0;
     };
}
#endif /* end of include guard: CHARACTER_HPP_RMVC7YT5 */
