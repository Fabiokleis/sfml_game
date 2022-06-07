#ifndef PLAYER_HPP_MTAYTDV0
#define PLAYER_HPP_MTAYTDV0
#include "character.hpp"

namespace Entities::Characters {
        class Player : public Character {
        private:
            int coin;
            int score;

        public:
            Player();

            Player(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height,
                   int cordx, int cordy, int coin, int life_number,
                   sf::Vector2u image_count, float switch_time, States state,
                   const std::string &path_name, float *delta_time);

            ~Player();

            int get_score() const;

            int get_coins() const;

            void init_physics();

            void restart(double x, double y, int _coin, int life, States _state);

            void on_collision(const std::string &object_type);

            void on_collision(const std::string &object_type, CollideStates cs);

            void update_input();

            void update_physics();

            void update_animation();

            void update_life_number();

            void handle_events(sf::Event &event);

            void handle_character_input(sf::Keyboard::Key key, bool is_pressed);

            void move(float dir_x, float dir_y);

            void update();
        };
    }


#endif /* end of include guard: PLAYER_HPP_MTAYTDV0 */
