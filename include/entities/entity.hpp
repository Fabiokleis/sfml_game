#ifndef ENTITY_HPP_RMVC7YT5
#define ENTITY_HPP_RMVC7YT5
#include <SFML/Graphics.hpp>
#include <iostream>
#include "entie.hpp"
#include "collider.hpp"
#include "animation.hpp"
#include "config.h"

namespace Entities {


    class Entity : public Entie {

        protected:
            sf::RectangleShape sprite;
            sf::IntRect shape;
            sf::Vector2f velocity;
            float gravity;

        public:
            Entity();
            Entity(Managers::GraphicManager *graphic_manager);
            ~Entity();

            sf::Vector2f& get_velocity();
            Managers::Collider get_collider();
            sf::RectangleShape get_sprite() const;
            sf::Vector2f get_position() const;
            void set_position(double x, double y);
            void set_size(double width, double height);
            void set_origin(double x, double y);
            void render();
            virtual void update() = 0;

        void set_velocity(float x, float y);
    };
}
#endif /* end of include guard: ENTITY_HPP_RMVC7YT5 */
