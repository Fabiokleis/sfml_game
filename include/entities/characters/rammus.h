#ifndef GAME_RAMMUS_H
#define GAME_RAMMUS_H
#include "enemy.hpp"
#include "fireBall.h"


namespace Entities::Characters {
    class Rammus: public Enemy{
    private:
        std::string type;
        int id;
        bool canAttack;
        int attackTimer;
        int cdr;
        bool moveleft;
        int moveTimer;
        int moveMax;
        FireBall* fireB;

    public:
        Rammus();
        Rammus(int id, Managers::GraphicManager *graphic_manager, double width, double height, int cordx, int cordy,
                int life_number,
                sf::Vector2u image_count, float switch_time, States state,
                const std::string &path_name, float *delta_time);
        ~Rammus();

        std::string get_type();
        int get_id() const;

        void update_animation();
        void move(float dir_x, float dir_y);
        void update();
        void update_move();
        void update_attack();
        void attack();
        FireBall* getFireB() { return fireB; }
    };
}


#endif