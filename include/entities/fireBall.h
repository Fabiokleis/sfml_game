#ifndef GAME_FIREBALL_H
#define GAME_FIREBALL_H
#define FIREBALL_PATH "enemies/FireBall.png"
#include "entity.hpp"

namespace Entities{
    class FireBall: public Entities::Entity{
    private:
        float *delta_time;
        float timeActive;
        float maxTimeActive;
        sf::Texture *texture;
        std::string type;

    public:
        bool isActive;
        FireBall(Managers::GraphicManager *graphic_manager, float* delta_time);
        FireBall();
        ~FireBall();
        void shoot(sf::Vector2f pos, sf::Vector2f vel);
        void update();
        void init_texture();
        void move(float dir_x, float dir_y);
        void on_collision();
        std::string get_type();
    };

}
#endif
