#include <SFML/Graphics.hpp>

#pragma once
class Tile {
    private:

		sf::RectangleShape body;

    public:
        Tile(float width, float left, float height, float top);
        ~Tile();
        sf::Vector2f get_position();
		void set_hitbox(float width, float left, float height, float top);
        bool check_collision(sf::RectangleShape body, float push);
        void move(float dx, float dy);
		sf::RectangleShape get_body();

};
