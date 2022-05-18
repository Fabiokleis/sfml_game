#include "animation.hpp"
using namespace Controllers;

Animation::Animation(sf::Texture* texture, sf::Vector2u image_count, float switch_time) {
    this->rect.width = texture->getSize().x / (float) image_count.x;
    this->rect.height = texture->getSize().y / (float) image_count.y;
    this->image_count = image_count;
    this->switch_time = switch_time;
    this->total_time = 0.0f;
    this->current_image.x = 0.0f;
}

Animation::~Animation() {

}

void Animation::update(int row, float delta_time, bool face_right) {
    this->current_image.y = row;
    this->total_time  += delta_time;

    if (this->total_time >= switch_time) {
        this->total_time -= switch_time;
        this->current_image.x++;

        if (this->current_image.x >= this->image_count.x) {
            this->current_image.x = 0;
        }
    }

    this->rect.top = this->current_image.y * this->rect.height;

    if (face_right) {
        this->rect.left = this->current_image.x * this->rect.width;
        this->rect.width = abs(this->rect.width);
    } else {
        this->rect.left = (this->current_image.x + 1) * abs(this->rect.width);
        this->rect.width = -abs(this->rect.width);
    }
}
