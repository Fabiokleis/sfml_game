#ifndef ENTITY_HPP_NUO0WDEY
#define ENTITY_HPP_NUO0WDEY
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities {

    class Entity {

        protected:
            sf::RectangleShape sprite;

        public:
            Entity(sf::Vector2f position, sf::Vector2f size);
            ~Entity();
            sf::Vector2f get_position() const;
            sf::Vector2f get_size() const;
    };
}
#endif /* end of include guard: ENTITY_HPP_NUO0WDEY */
