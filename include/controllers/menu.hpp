#ifndef MENU_HPP_S0BISRCL
#define MENU_HPP_S0BISRCL
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "image.hpp"
#include "text.hpp"

namespace Controllers {

    class Menu {
        private:
            Entities::Image &menu_image;
            std::vector<Entities::Text>& text_options;
            
        public:
            Menu(Entities::Image& menu_image, sf::Vector2f position, std::vector<Entities::Text>& text_options);
            ~Menu();

            sf::RectangleShape get_sprite();
            void populate_option(Entities::Text& options);
    };
}


#endif /* end of include guard: MENU_HPP_S0BISRCL */
