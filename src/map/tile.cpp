#include <iostream>
#include "tile.hpp"
using namespace std;

Tile::Tile(float width, float left, float height, float top) {
    this->body.setSize(sf::Vector2f(width, height));
    this->body.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    this->body.setPosition(sf::Vector2f(left, top));
}

sf::Vector2f Tile::get_position() {
    return this->body.getPosition();
}

void Tile::set_hitbox(float width, float left, float height, float top) {
    this->body.setSize(sf::Vector2f(width, height));
    this->body.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    this->body.setPosition(sf::Vector2f(left, top));
}

sf::RectangleShape Tile::get_body() {
    return this->body;
}

bool Tile::check_collision(sf::RectangleShape &body, sf::Vector2f dir) {
    sf::Vector2f this_pos = this->get_position();
    sf::Vector2f this_siz = this->body.getSize() / 2.0f;
    sf::Vector2f other_pos = body.getPosition();
    sf::Vector2f other_siz = body.getSize() / 2.0f;

    float delta_x = other_pos.x - this_pos.x + this_siz.x;
    float delta_y = other_pos.y - this_pos.y + this_siz.y;

    float intersec_x = abs(delta_x) - (other_siz.x + this_siz.x);
    float intersec_y = abs(delta_y) - (other_siz.y + this_siz.y);

    if (intersec_x < 0.0f && intersec_y < 0.0f) {
        if (intersec_x > intersec_y) {
            if (dir.x < 0.0f && delta_x > 0.0f) {
                body.move(-dir.x, 0.0f);
            } else if (dir.x > 0.0f && delta_x < 0.0f) {
                body.move(-dir.x, 0.0f);
            }
        } else {
            if (delta_y > 0.0f && dir.y > 0.0f) {
                body.move(0.0f, -dir.y);
            } else if (delta_y < 0.0f) {
                body.move(0.0f, -dir.y);
            }
        }
        return true;
    }


    return false;
}

void Tile::move(float dx, float dy) {
    this->body.move(dx, dy);
}

Tile::~Tile() {}