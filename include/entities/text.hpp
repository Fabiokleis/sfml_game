#ifndef TEXT_HPP_BC9SOBZY
#define TEXT_HPP_BC9SOBZY
#include <SFML/Graphics/Text.hpp>
#include "config.h"

namespace Entities {

    class Text {
        private:
            sf::Text text;
            sf::Font font;
            sf::Color default_color;
            unsigned default_style;
            sf::Color default_outline_color;
            float default_thick_size;

        public:
            Text(const std::string& path_name, unsigned int size, float x, float y, sf::Color color = sf::Color::White,
                 unsigned style = 0, sf::Color outline = sf::Color::Transparent, float thick = 0.0f, const std::string& str = "");
            Text();
            ~Text();
            void set_text(const std::string& str);
            void set_position(sf::Vector2f position);
            void reset();
            void set_attr(sf::Color color, sf::Color outline_color, float thick, unsigned style);
            sf::Text& get_text();

    };
}


#endif /* end of include guard: TEXT_HPP_BC9SOBZY */
