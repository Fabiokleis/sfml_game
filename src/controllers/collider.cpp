#include <iostream>
#include "collider.hpp"
using namespace Controllers;

Collider::Collider(sf::RectangleShape &body) : body(body) {}

sf::Vector2f Collider::get_position() {
    return this->body.getPosition();
}

sf::Vector2f Collider::get_size() {
    return this->body.getSize();
}

void Collider::set_body(sf::RectangleShape &nboby) {
    this->body = nboby;
}

void Collider::move(float dx, float dy) {
    this->body.move(dx, dy);
}

Collider::~Collider() {}

bool Collider::check_collision(Collider other, sf::Vector2f& dir) {
    sf::Vector2f this_pos = this->get_position();
    sf::Vector2f this_siz = this->get_size() / 2.0f;
    sf::Vector2f other_pos = other.get_position();
    sf::Vector2f other_siz = other.get_size() / 2.0f;

    float delta_x = other_pos.x - this_pos.x + this_siz.x;
    float delta_y = other_pos.y - this_pos.y + this_siz.y;

    float intersect_x = std::abs(delta_x) - (this_siz.x + other_siz.x);
    float intersect_y = std::abs(delta_y) - (this_siz.y + other_siz.y);

    if (intersect_x < 0.0f && intersect_y < 0.0f) {
        if (intersect_x > intersect_y) {
            if (delta_x > 0.0f) {
                other.move(-intersect_x, 0.0f);
                dir.x = 1.0f;
            } else if (delta_x < 0.0f){
                other.move(intersect_x, 0.0f);
                dir.x = -1.0f;
            }
        } else {
            if (delta_y > 0.0f) {
                other.move(0.0f, -intersect_y);
                dir.y = 1.0f;
            } else if (delta_y < 0.0f) {
                other.move(0.0f, intersect_y);
                dir.y = -1.0f;
            }
        }
        return true;
    }

    return false;
}
