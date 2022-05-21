#ifndef ENTITY_HPP_NUO0WDEY
#define ENTITY_HPP_NUO0WDEY
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities {

    class Entity {

        protected:
            sf::RectangleShape sprite;
            bool life;

        public:
            Entity(sf::Vector2f position, sf::Vector2f size);
            Entity();
            ~Entity();
            sf::RectangleShape get_sprite() const;
            const sf::Vector2f get_position() const;
            bool get_life();
            void set_position(sf::Vector2f position);
            void set_life(bool flag);
            void set_size(sf::Vector2f size);
    };
}
#endif /* end of include guard: ENTITY_HPP_NUO0WDEY */
