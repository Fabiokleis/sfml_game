#ifndef CHARACTER_HPP_WHBHED8U
#define CHARACTER_HPP_WHBHED8U
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include "graphic_manager.hpp"
#include "config.h"
#include "entity.hpp"
#include "animation.hpp"

namespace Entities::Characters {
        enum CollideStates {
            top = 0,
            right,
            left,
            ground,
            colliding,
            not_colliding,
        };

        enum States {
            idle = 0,
            walking_right,
            walking_left,
            down,
            jumping,
            falling,
            falling_right,
            falling_left,
            dead,
        };

        class Character : public Entity {
        private:
            Managers::Animation *animation;
            sf::Texture *texture;

        protected:
            CollideStates collide_state;
            States state;
            States last_state;
            std::string path_name;
            sf::Vector2u image_count;
            float jump_height;
            float acceleration;
            float *delta_time;
            float switch_time;
            int life_number;

        public:
            Character();

            Character(Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                      int life_number,
                      sf::Vector2u image_count, float switch_time, States state,
                      const std::string &path_name, float *delta_time);

            virtual ~Character();

            int get_life_number() const;

            States get_state();

            CollideStates get_collide_state();

            Managers::Animation &get_animation();

            void set_last_state(States s);

            void set_state(States s);

            void set_collide_state(CollideStates s);

            void init_texture();

            virtual void on_collision(const std::string &object_type) = 0;

            virtual void update_animation() = 0;

            virtual void update_life_number() = 0;

            virtual void update_physics() = 0;

            virtual void move(float dir_x, float dir_y) = 0;

            virtual void update() = 0;
        };
    }

#endif /* end of include guard: CHARACTER_HPP_WHBHED8U */
