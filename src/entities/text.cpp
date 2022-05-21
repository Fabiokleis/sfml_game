#include <iostream>
#include "text.hpp"
using namespace Entities;


Text::Text(const std::string& path_name, unsigned int size, float x, float y, sf::Color color, const std::string& str) {
    std::string path = RESOURCE_PATH;
    if (!this->font.loadFromFile(path+path_name)) {
        std::cout << "ERROR:GAME::COULD NOT LOAD PIXEL FONT." << std::endl;
    }
    this->text.setFont(this->font);
    this->text.setCharacterSize(size);
    this->text.setPosition(x, y);
    this->text.setFillColor(color);
    this->text.setString(str);
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
