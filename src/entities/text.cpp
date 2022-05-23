#include <iostream>
#include "text.hpp"
using namespace Entities;


Text::Text(const std::string& path_name, unsigned int size, float x, float y, sf::Color color,
           unsigned style, sf::Color outline, float thick, const std::string& str)
{
    std::string path = RESOURCE_PATH;
    if (!this->font.loadFromFile(path+path_name)) {
        std::cout << "ERROR:GAME::COULD NOT LOAD PIXEL FONT." << std::endl;
    }
    this->default_color = color;
    this->default_outline_color = outline;
    this->default_thick_size = thick;
    this->default_style = style;
    this->text.setFont(this->font);
    this->text.setCharacterSize(size);
    this->text.setOutlineColor(default_outline_color);
    this->text.setOutlineThickness(default_thick_size);
    this->text.setStyle(default_style);
    this->text.setFillColor(default_color);
    this->text.setPosition(x, y);
    this->text.setString(str);
    this->text.setOrigin(size / 2.0f, size / 2.0f);
}

Text::Text() = default;

Text::~Text() = default;

void Text::set_text(const std::string& str) {
    this->text.setString(str);
}

void Text::set_position(sf::Vector2f position) {
    this->text.setPosition(position);
}

sf::Text& Text::get_text() {
    return this->text;
}

void Text::set_attr(sf::Color color, sf::Color outline_color, float thick, unsigned style) {
    this->text.setFillColor(color);
    this->text.setOutlineThickness(thick);
    this->text.setOutlineColor(outline_color);
    this->text.setStyle(style);
}

void Text::reset() {
    this->text.setFillColor(default_color);
    this->text.setOutlineThickness(default_thick_size);
    this->text.setOutlineColor(default_outline_color);
    this->text.setStyle(default_style);
}
