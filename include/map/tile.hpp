#include <SFML/Graphics.hpp>

#pragma once
class Tile {
    private:
        sf::RectangleShape shape;

    public:
        Tile();
        Tile(float x, float y, float grid_size_f, sf::Texture* texture);
        ~Tile();

        void update();
        void render(sf::RenderTarget* target);

};