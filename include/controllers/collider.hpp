#ifndef COLLIDER_HPP_GUEOIKJ9
#define COLLIDER_HPP_GUEOIKJ9
#include <SFML/Graphics.hpp>

namespace Controllers {

    class Collider {
        private:
    		sf::RectangleShape &body;
    
        public:
            Collider(sf::RectangleShape &body);
            ~Collider();
            sf::Vector2f get_position();
            void set_body(sf::RectangleShape &nboby);
            bool check_collision(Collider other, sf::Vector2f& dir, bool needs_move);
            bool move_on_collision();
            void move(float dx, float dy);
            sf::Vector2f get_half_size();
    };
}
#endif /* end of include guard: COLLIDER_HPP_GUEOIKJ9 */
