#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H
#include "character.hpp"

namespace Entities::Characters {
        class Enemy : public Character {
        protected:
            int id;
        public:
            Enemy();

            Enemy(Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                  int life_number,
                  sf::Vector2u image_count, float switch_time, States state,
                  const std::string &path_name, float *delta_time);

            ~Enemy();


            bool operator==(Enemy &other);
            int get_id() const;
            void on_collision(const std::string &object_type);

            void update_life_number();

            void update_physics();

            virtual void update_animation() = 0;

            virtual void move(float dir_x, float dir_y) = 0;

            virtual void update() = 0;
        };
    }
#endif //GAME_ENEMY_H
