#include <iostream>
#include <SFML/Graphics.hpp>

#pragma once
class Animation {
    private:
        sf::Vector2u image_count;
        sf::Vector2u current_image;
        sf::Clock clock;

        float total_time;
        float switch_time;

    public:
        sf::IntRect rect;

    public:
        Animation(sf::Texture *texture, sf::Vector2u image_count, float switch_time);
        ~Animation();
        void update(int row, float delta_time, bool face_right);

};