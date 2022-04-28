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

bool Tile::check_collision(sf::RectangleShape body, float push) {
    sf::Vector2f this_pos = this->get_position();
    sf::Vector2f this_siz = this->body.getSize() / 2.0f;
    sf::Vector2f other_pos = body.getPosition();
    sf::Vector2f other_siz = body.getSize() / 2.0f;

    float mod_x = other_pos.x - this_pos.x;
    float mod_y = other_pos.y - this_pos.y;
    float intersect_x = abs(mod_x) - (other_pos.x + this_siz.x);
    float intersect_y = abs(mod_y) - (other_pos.y + this_siz.y);

    if (intersect_x < 0.0f && intersect_y < 0.0f) {
        push = min(max(push, 0.0f), 1.0f);

        if (abs(intersect_x) < abs(intersect_y)) {
            if (mod_x > 0.0f) {
                move(intersect_x * (1.0f - push), 0.0f);
                body.move(-intersect_x * push, 0.0f);
            } else {
                move(-intersect_x * (1.0f - push), 0.0f);
                body.move(intersect_x * push, 0.0f);
            }
        } else {
            if (mod_y > 0.0f) {
                move(0.0f, intersect_y * (1.0f - push));
                body.move(0.0f, -intersect_y * push);
            } else {
                move(0.0f, -intersect_y * (1.0f - push));
                body.move(0.0f, intersect_y * push);
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