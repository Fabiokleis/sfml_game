#include <SFML/Graphics.hpp>

#pragma once
class Collider {
    private:
		sf::RectangleShape &body;

    public:
        Collider(sf::RectangleShape &body);
        ~Collider();
        sf::Vector2f get_position();
        void set_body(sf::RectangleShape &nboby);
        bool check_collision(Collider other, sf::Vector2f& dir);
        void move(float dx, float dy);
        sf::Vector2f get_size();
};
