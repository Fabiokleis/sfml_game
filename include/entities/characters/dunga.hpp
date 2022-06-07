#ifndef GAME_DUNGA_H
#define GAME_DUNGA_H
#include "characters/enemy.hpp"

namespace Entities{
    namespace Characters {
        class Dunga : public Characters::Enemy {
        private:
            std::string type;
            int id;

        public:
            Dunga();
            Dunga(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                  int life_number,
                  sf::Vector2u image_count, float switch_time, States state,
                  const std::string &path_name, float *delta_time);
            ~Dunga();

            std::string get_type();
            int get_id() const;

            void update_animation();
            void move(float dir_x, float dir_y);
            void update();
            void update_move();
        };
    }
}


#endif //GAME_DUNGA_H
