#ifndef TEXT_HPP_BC9SOBZY
#define TEXT_HPP_BC9SOBZY
#include <SFML/Graphics/Text.hpp>
#include "config.h"

namespace Entities {

    class Text {
        private:
            sf::Text text;
            sf::Font font;

        public:
            Text(const std::string& path_name, unsigned size, float x, float y, sf::Color color, const std::string& str = "");
            Text();
            ~Text();
            void set_text(const std::string& str);
            void set_position(sf::Vector2f position);
            sf::Text& get_text();

    };
}


#endif /* end of include guard: TEXT_HPP_BC9SOBZY */
