#ifndef ENTITY_HPP_RMVC7YT5
#define ENTITY_HPP_RMVC7YT5
#include <SFML/Graphics.hpp>
#include <iostream>
#include "entie.hpp"
#include "animation.hpp"
#include "config.h"

namespace Entities {

    class Entity : public Entie {

        protected:
            sf::RectangleShape sprite;
            sf::IntRect shape;
            sf::Vector2f velocity;
            float gravity;
            std::string type;

        public:
            Entity();
            Entity(Managers::GraphicManager *graphic_manager);
            ~Entity();

            sf::Vector2f& get_velocity();
            sf::RectangleShape get_sprite() const;
            sf::Vector2f get_position() const;
            sf::Vector2f get_size() const;
            sf::Vector2f get_half_size() const;
            std::string get_type() const;
            void set_graphic_manager(Managers::GraphicManager *gp);
            void set_position(double x, double y);
            void set_size(double width, double height);
            void set_origin(double x, double y);
            void set_velocity(float x, float y);
            void set_color(sf::Color color);
            void set_out_color(sf::Color color);
            void render();
            virtual void move(float dir_x, float dir_y) = 0;
            virtual void update() = 0;

    };
}
#endif /* end of include guard: ENTITY_HPP_RMVC7YT5 */
