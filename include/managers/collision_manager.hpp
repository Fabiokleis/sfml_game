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
            Listas::Lista<Entities::Obstacles::Obstacle> obstacles;
            std::vector<Entities::Characters::Enemy*> enemies;

            float intersect_x;
            float intersect_y;
            float delta_x;
            float delta_y;

        public:
            CollisionManager();
            CollisionManager(const Listas::Lista<Entities::Obstacles::Obstacle>& obstacles);
            ~CollisionManager();
            void collision_control(Entities::Characters::Player *other);
            void populate_enemies_vector(Entities::Characters::Enemy *one);
            bool check_collision(const Entities::Entity& entity, const Entities::Entity& other);
            void update_intersects_characters(Entities::Characters::Character &one, Entities::Characters::Character &other, sf::Vector2f &dir_one,
                                 sf::Vector2f &dir_other);
            void update_intersects_obstacle_character(Entities::Obstacles::Obstacle &one, Entities::Characters::Character &other, sf::Vector2f &dir, bool needs_move);
    };
}
#endif /* end of include guard: COLLIDER_HPP_GUEOIKJ9 */
