#ifndef CHARACTER_HPP_WHBHED8U
#define CHARACTER_HPP_WHBHED8U
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include "graphic_manager.hpp"
#include "config.h"
#include "entity.hpp"
#include "animation.hpp"

namespace Entities {

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


        protected:
            CollideStates collide_state;
            States state;
            States last_state;
            sf::Texture texture;
            std::string path_name;
            sf::Vector2u image_count;
            float jump_height;
            float acceleration;
            float delta_time;
            float switch_time;
            int life_number;

        public:
            Character();
            Character(Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy, int life_number,
                      sf::Vector2u image_count, float switch_time, States state,
                      const std::string &path_name);

            virtual ~Character();
            void reset_clock(float dt);
            int get_life_number() const;
            States get_state();
            CollideStates get_collide_state();
            Managers::Animation& get_animation();
            void set_last_state(States s);
            void set_state(States s);
            void set_collide_state(CollideStates s);
            void init_texture();
            virtual void on_collision(const std::string& object_type) = 0;
            virtual void update_animation() = 0;
            virtual void update_life_number() = 0;
            virtual void handle_events(sf::Event& event) = 0;
            virtual void update_physics() = 0;
            virtual void handle_character_input(sf::Keyboard::Key key, bool is_pressed) = 0;
            virtual void update_input() = 0;
            virtual void move(float dir_x, float dir_y) = 0;
            virtual void update() = 0;
    };
}

#endif /* end of include guard: CHARACTER_HPP_WHBHED8U */
