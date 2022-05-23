#ifndef CHARACTER_HPP_RMVC7YT5
#define CHARACTER_HPP_RMVC7YT5
#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.hpp"
#include "collider.hpp"
#include "animation.hpp"
#include "config.h"

namespace Entities {

    enum State {
        idle = 0,
        jumping,
        right,
        left,
        falling,
        ground,
    };

    class Character : public Entity {
        private:
            Controllers::Animation *animation{};

        protected:
            bool life;
            sf::IntRect shape;
            sf::Vector2f velocity;
            sf::Texture texture;
            std::string path_name;
            sf::Vector2u image_count;
            float switch_time{};
            State state;

        public:
            Character(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord,
                      sf::Vector2u image_count, float switch_time, State state, std::string path_name);

            Character();
            ~Character();
            void init_texture();
            sf::Vector2f& get_velocity();
            Controllers::Collider get_collider();
            Controllers::Animation& get_animation();
            void set_life(bool flag);
            bool get_life();
            void set_state(State s);
            void set_rect(sf::IntRect rect);
            virtual void move(float dir_x, float dir_y) = 0;
     };
}
#endif /* end of include guard: CHARACTER_HPP_RMVC7YT5 */
