#ifndef GAME_RAMMUS_H
#define GAME_RAMMUS_H
#include "enemy.hpp"
#include "fireBall.h"
#include "player.hpp"


namespace Entities::Characters {
    class Rammus: public Enemy{
    private:
        bool canAttack;
        int attackTimer;
        int cdr;
        FireBall* fireB;
        Player* p1;

    public:
        Rammus();
        Rammus(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                int life_number,
                sf::Vector2u image_count, float switch_time, States state,
                const std::string &path_name, float *delta_time);
        ~Rammus();


        void update_animation();
        void move(float dir_x, float dir_y);
        void update();
        void update_move();
        void update_attack();
        void attack();
        void set_player(Player* player);
        FireBall* getFireB() { return fireB; }
    };
}


#endif