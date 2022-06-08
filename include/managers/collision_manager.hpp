#ifndef COLLIDER_HPP_GUEOIKJ9
#define COLLIDER_HPP_GUEOIKJ9
#include <SFML/Graphics.hpp>
#include "../entities/characters/enemy.hpp"
#include "ListaEntities.h"
#include "coin.hpp"
#include "characters/player.hpp"

namespace Managers {

    class CollisionManager {
        private:
            Listas::Lista<Entities::Obstacles::Obstacle> &obstacles;
            std::vector<Entities::Characters::Enemy*> &enemies;

            float intersect_x;
            float intersect_y;
            float delta_x;
            float delta_y;

        public:
            CollisionManager(Listas::Lista<Entities::Obstacles::Obstacle> &obstacles, std::vector<Entities::Characters::Enemy*> &enemies);
            ~CollisionManager();
            void collision_control(Entities::Characters::Player *other);
            bool check_collision(const Entities::Entity& entity, const Entities::Entity& other);
            void update_intersects_characters(Entities::Characters::Character *one, Entities::Characters::Character *other, sf::Vector2f &dir_one,
                                 sf::Vector2f &dir_other);
            void update_intersects_obstacle_character(Entities::Obstacles::Obstacle *one, Entities::Characters::Character *other, sf::Vector2f &dir, bool needs_move);
            friend std::ostream& operator<< (std::ostream &out, CollisionManager const& c) {
                out << "delta_x: " << c.delta_x << std::endl;
                out << "delta_y: " << c.delta_y << std::endl;
                out << "intersect_x: " << c.intersect_x << std::endl;
                out << "intersect_y: " << c.intersect_y << std::endl;

            }
    };

}
#endif /* end of include guard: COLLIDER_HPP_GUEOIKJ9 */
