#ifndef ENTITY_HPP_NUO0WDEY
#define ENTITY_HPP_NUO0WDEY
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities {

    class Entity {

        protected:
            sf::RectangleShape sprite;


        public:
            Entity(double x, double y, double width, double height);
            Entity();
            ~Entity();
            sf::RectangleShape get_sprite() const;
            sf::Vector2f get_position() const;
            void set_position(double x, double y);
            void set_size(double width, double height);
            void set_origin(double x, double y);
            void set_color(sf::Color color);
            void set_texture(sf::Texture *texture);
            void set_thickness(float thick);
            void set_outline_color(sf::Color color);

    };
}
#endif /* end of include guard: ENTITY_HPP_NUO0WDEY */
