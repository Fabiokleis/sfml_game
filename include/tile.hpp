#include <SFML/Graphics.hpp>

#pragma once
class Tile {
    private:
        sf::RectangleShape shape;

    public:
        Tile();
        Tile(float x, float y, float grid_size_f);
        ~Tile();
        const sf::FloatRect getBounds() const;
        void update();
        void render(sf::RenderTarget* target);

};