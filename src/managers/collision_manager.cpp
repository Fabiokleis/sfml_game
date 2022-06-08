#include <iostream>
#include "collision_manager.hpp"
using namespace Managers;

CollisionManager::CollisionManager(Listas::Lista<Entities::Obstacles::Obstacle> &obstacles, std::vector<Entities::Characters::Enemy*> &enemies) :
    obstacles(obstacles), enemies(enemies), intersect_y(0), intersect_x(0), delta_x(0), delta_y(0)
{
    std::cout << "len1: " << obstacles.getLen() << std::endl;
    std::cout << "len2: " << this->obstacles.getLen() << std::endl;
}

CollisionManager::~CollisionManager() {
    for(int i = this->obstacles.getLen()-1; i >= 0; i--) {
        this->obstacles.pop(this->obstacles.getItem(i));
    }
}

// verify collision between any entity, set all variables to manage overlaps and returns true if collide
bool CollisionManager::check_collision(const Entities::Entity& enti, const Entities::Entity& other)
{

    sf::Vector2f this_pos = enti.get_position();
    sf::Vector2f this_half_size = enti.get_half_size();
    sf::Vector2f other_pos = other.get_position();
    sf::Vector2f other_half_size = other.get_half_size();


    this->delta_x = other_pos.x - this_pos.x;
    this->delta_y = other_pos.y - this_pos.y;

    this->intersect_x = std::abs(delta_x) - (this_half_size.x + other_half_size.x);
    this->intersect_y = std::abs(delta_y) - (this_half_size.y + other_half_size.y);

    if (this->intersect_x < 0.0f && this->intersect_y < 0.0f) {

        return true;
    }

    return false;
}


// update the character position when object and a character collides and the character needs to move when this happen
void CollisionManager::update_intersects_obstacle_character(Entities::Obstacles::Obstacle *one,
                                                            Entities::Characters::Character *other, sf::Vector2f &dir,
                                                            bool needs_move)
{
    if (needs_move) {
        if (this->intersect_x > this->intersect_y) {
            if (this->delta_x > 0.0f) {
                other->move(-this->intersect_x, 0.0f);
                other->set_collide_state(Entities::Characters::right);
                dir.x = 1.0f;

            } else {
                other->move(this->intersect_x, 0.0f);
                other->set_collide_state(Entities::Characters::left);
                dir.x = -1.0f;
            }
        } else {
            if (this->delta_y > 0.0f) {
                other->set_position(other->get_position().x,  one->get_position().y - other->get_position().y);
                other->set_collide_state(Entities::Characters::top);
            } else {
                other->set_position(other->get_position().x, one->get_position().y - one->get_size().y + 22);
                other->set_collide_state(Entities::Characters::ground);
            }
        }
    }

}
// update intersects between two characters;
void CollisionManager::update_intersects_characters(Entities::Characters::Character *one,
                                                    Entities::Characters::Character *other, sf::Vector2f &dir_one,
                                                    sf::Vector2f &dir_other) {
    if (this->intersect_x > this->intersect_y) {
        if (this->delta_x > 0.0f) {
            one->move(-this->intersect_x, 0.0f);
            other->move(this->intersect_x, 0.0f);
            dir_other.x = -1.0f;
            dir_one.x = 1.0f;

        } else {
            one->move(this->intersect_x, 0.0f);
            other->move(-this->intersect_x, 0.0f);
            dir_one.x = -1.0f;
            dir_other.x = 1.0f;
        }
    } else {
        if (this->delta_y > 0.0f) {
            one->move(0.0f, -this->intersect_y);
            other->move(0.0f, this->intersect_y);
            dir_one.y = 1.0f;
            dir_other.y = -1.0f;
        } else {
            one->move(0.0f, this->intersect_y);
            other->move(0.0f, -this->intersect_y);
            dir_one.y = -1.0f;
            dir_one.y = 1.0f;
        }
    }
}



void CollisionManager::collision_control(Entities::Characters::Player *other) {
    // verify collision with all objects

    for (int i = 0; i < this->obstacles.getLen(); i++) {
        auto obstacle = this->obstacles.getItem(i);
        // player collision
        if (this->check_collision(*obstacle, *other)) {
            std::cout << "obs_type: " << obstacle->get_type() << std::endl;
            std::cout << "colidiu" << std::endl;
            this->update_intersects_obstacle_character(obstacle, other, other->get_velocity(), true);
            other->on_collision(obstacle->get_type());
        }

//        // enemies collision
//        for (auto &enemy : this->enemies) {
//            if (obstacle->get_type() != "coin") { // remove coin from obstacle types that enemy can collide
//                if (this->check_collision(*obstacle, *enemy)) {
//                    this->update_intersects_obstacle_character(*obstacle, *enemy, enemy->get_velocity(), true);
//                    enemy->on_collision(obstacle->get_type());
//                }
//            }
//        }
    }
//
//    // verify collision between characters
//    for (auto &enemy : this->enemies) {
//        if (this->check_collision(*other, *enemy)) {
//            this->update_intersects_characters(*other, *enemy, other->get_velocity(), enemy->get_velocity());
//        }
//    }
}

