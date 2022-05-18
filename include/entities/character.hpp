#ifndef CHARACTER_HPP_RMVC7YT5
#define CHARACTER_HPP_RMVC7YT5
#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.hpp"
#include "collider.hpp"
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
        protected:
            sf::IntRect shape;
            sf::Vector2f velocity;
            sf::Texture texture;
            std::string path_name;
            State state;

        public:
            Character(sf::Vector2f size, sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f cord, std::string name);
            ~Character();
            void init_texture();
            sf::Vector2f& get_velocity();
            void set_state(State s);
            Controllers::Collider get_collider();
            virtual void move(float dir_x, float dir_y) = 0;
     };
}
#endif /* end of include guard: CHARACTER_HPP_RMVC7YT5 */
