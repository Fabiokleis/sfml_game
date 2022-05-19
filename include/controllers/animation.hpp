#ifndef ANIMATION_HPP_07XAXBPH
#define ANIMATION_HPP_07XAXBPH
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Controllers {

    class Animation {
        private:
            sf::Vector2u image_count;
            sf::Vector2u current_image;
            float total_time{};
            float switch_time{};

        public:
            sf::IntRect rect;

        public:
            Animation(sf::Vector2u size, sf::Vector2u image_count, float switch_time);
            ~Animation();
            void update(int row, float delta_time, bool face_right);
    };
}
#endif /* end of include guard: ANIMATION_HPP_07XAXBPH */
