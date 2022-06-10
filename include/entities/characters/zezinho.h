#ifndef GAME_ZEZINHO_H
#define GAME_ZEZINHO_H
#include "enemy.hpp"

namespace Entities::Characters{
    class Zezinho: public Enemy{
    private:

    public:
        Zezinho();
        Zezinho(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
              int life_number,
              sf::Vector2u image_count, float switch_time, States state,
              const std::string &path_name, float *delta_time);
        ~Zezinho();
        void update_animation();
        void move(float dir_x, float dir_y);
        void update();
        void update_move();
    };
}



#endif //GAME_ZEZINHO_H
