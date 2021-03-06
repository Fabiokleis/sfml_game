#include "characters/player.hpp"
using namespace Entities::Characters;

Player::Player() : Character(), coin() {}

Player::Player(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height, int cordx, int cordy,
               int coin, int life_number, sf::Vector2u image_count, float switch_time, States state,
               const std::string &path_name, float* delta_time) :
    Character(graphic_manager, width, height, cordx, cordy, life_number, image_count, switch_time, state, path_name, delta_time),
    coin(coin)
{
    this->set_position(x, y);
    this->set_velocity(0.0f, 0.0f);
    this->init_physics();
    this->set_origin(width/2, height/2);
    this->score = 0;
    this->type = "player";
}

Player::~Player() {}

int Player::get_coins() const {
    return this->coin;
}

void Player::init_physics() {
    this->jump_height = 20.0f;
    this->acceleration = 200.0f;
}

void Player::restart(double x, double y, int _coin, int life, States _state) {
    this->state = _state;
    this->sprite.setPosition(x, y);
    this->coin = _coin;
    this->life_number = life;
    this->velocity.x = 0.0f;
    this->velocity.y = 0.0f;
    this->score = 0;
}

void Player::on_collision(const std::string &object_type, CollideStates cs) {
    if(object_type == "dunga" || object_type == "zezinho" || object_type == "rammus") {
        if (cs == top) {
            score++;
            collide_state = ground;
        } else {
            state = dead;
        }
    }

    this->update_life_number();
}

void Player::on_collision(const std::string& object_type) {
    if (object_type != "coin") {

        if (object_type == "spike") {
            this->state = dead;
        }

    } else {
        this->coin++;
    }
    this->update_life_number();
}

int Player::get_score() const {
    return score;
}

void Player::operator++() {
    this->score++;
}



void Player::update_life_number() {
    if (state == dead) {
        this->life_number--;
    } else {
        if (this->life_number <= 0) {
            this->life_number = 5;

        } else if (this->life_number >= 1) {
            // increase life number by 10 coins collected and reset coin score
            if (this->coin == 10) {
                this->life_number++;
                this->coin = 0;
            }
        }
    }
}

void Player::handle_events(sf::Event &event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            this->handle_character_input(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            this->handle_character_input(event.key.code, false);
            break;

        default:
            break;
    }

}

void Player::move(const float dir_x, const float dir_y) {
    // accelerate
    this->velocity.x += dir_x * this->acceleration;

    // jump
    if (state == jumping && this->collide_state == ground) {
        float jump = (2 * this->gravity * this->jump_height);
        this->velocity.y = -(static_cast<float>(jump));
        this->collide_state = not_colliding;
    }
}

void Player::update_physics() {
    this->velocity.y += this->gravity;
    this->sprite.move(this->velocity * (*this->delta_time));
}

void Player::update_input() {
    this->velocity.x = 0.0f; // reset velocity on x
    // jaime movement - kb
    if (state == walking_left || state == falling_left) {
        this->move(-1.0f, 0.0f);
    } else if (state == walking_right || state == falling_right) {
        this->move(1.0f, 0.0f);
    } else if (state == down) {
        this->move(0.0f, 1.0f);
    } else if (state == jumping && this->collide_state == ground) {
        this->move(0.f, -1.f);
    }
}

void Player::handle_character_input(sf::Keyboard::Key key, bool is_pressed) {
    if (is_pressed) {
        if (this->collide_state == ground) {
            if (key == sf::Keyboard::Space) {
                state = jumping;
            } else if (key == sf::Keyboard::S) {
                state = down;
            } else if (key == sf::Keyboard::A) {
                state = walking_left;
            } else if (key == sf::Keyboard::D) {
                state = walking_right;
            }
        } else {
            if (key == sf::Keyboard::A) {
                state = falling_left;

            } else if (key == sf::Keyboard::D) {
                state = falling_right;
            } else {
                state = falling;
            }

        }
    } else {
        state = idle;
        if (key == sf::Keyboard::Space && collide_state == not_colliding) {
            state = falling;
        }
    }
}

void Player::update_animation() {
//    enum States {         row
//        idle = 0,         0
//        walking_right,    1
//        walking_left,     1 flipped
//        down,             4
//        jumping,          2
//        falling,          3
//        jumping_right     2
//        jumping_left      2 flipped
//        dead,             5
//    };

    switch (this->state) {
        case 0: // idle
            if (this->last_state == walking_right || this->last_state == idle) {
                this->get_animation().update(0, (*this->delta_time), true);
            } else if (this->last_state == walking_left) {
                this->get_animation().update(0, (*this->delta_time), false);
            }
            break;
        case 1: // walking_right
            this->get_animation().update(1, (*this->delta_time), true);
            break;
        case 2: // walking_left
            this->get_animation().update(1, (*this->delta_time), false);
            break;
        case 3: // down
            this->get_animation().update(4, (*this->delta_time), true);
            break;
        case 4: // jumping
            if (this->last_state == walking_right) {
                this->get_animation().update(2, (*this->delta_time), true);
            } else if (this->last_state == walking_left) {
                this->get_animation().update(2, (*this->delta_time), false);
            } else {
                this->get_animation().update(0, (*this->delta_time), true);
            }
            break;
        case 5: // falling
            if (this->velocity.x > 0.0f) {
                this->get_animation().update(3, (*this->delta_time), true);
            } else if (this->velocity.x < 0.0f) {
                this->get_animation().update(3, (*this->delta_time), false);
            }
            break;
        case 6: // falling_right
            this->get_animation().update(3, (*this->delta_time), true);
            break;
        case 7: // falling_left
            this->get_animation().update(3, (*this->delta_time), false);
            break;
        case 8: // dead
            if (this->last_state == falling_right || this->last_state == walking_right || this->last_state == idle) {
                this->get_animation().update(5, (*this->delta_time), true);
            } else if (this->last_state == falling_left || this->last_state == walking_left) {
                this->get_animation().update(5, (*this->delta_time), false);
            }
            break;
        default:

            break;
    }

    this->sprite.setTextureRect(this->get_animation().rect);
    this->last_state = state;
}

void Player::update() {
    this->update_input();
    this->update_physics();
    this->update_animation();
}
