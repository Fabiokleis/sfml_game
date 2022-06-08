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
                other->set_position(other->get_position().x - (intersect_x), other->get_position().y);
                other->set_collide_state(Entities::Characters::right);
                dir.x = 0.0f;
            } else {
                other->set_position(other->get_position().x + (intersect_x), other->get_position().y);
                other->set_collide_state(Entities::Characters::left);
                dir.x = 0.0f;
            }
        } else {
            if (this->delta_y > 0.0f) {
                other->set_position(other->get_position().x, other->get_position().y - (intersect_y));
                other->set_collide_state(Entities::Characters::top);
                dir.y = 0.0f;
            } else {
                other->set_position(other->get_position().x, other->get_position().y + (intersect_y));
                other->set_collide_state(Entities::Characters::ground);
                dir.y = 0.0f;
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
            other->set_position(other->get_position().x - (intersect_x), other->get_position().y);
            one->set_position(one->get_position().x + (intersect_x), one->get_position().y);
            other->set_collide_state(Entities::Characters::right);
            one->set_collide_state(Entities::Characters::left);
            dir_other.x = 0.0f;
            dir_one.x = 0.0f;
        } else {
            other->set_collide_state(Entities::Characters::left);
            one->set_collide_state(Entities::Characters::right);
            other->set_position(other->get_position().x + (intersect_x), other->get_position().y);
            one->set_position(one->get_position().x - (intersect_x), one->get_position().y);
            dir_other.x = 0.0f;
            dir_one.x = 0.0f;
        }
    } else {
        if (this->delta_y > 0.0f) {
            other->set_collide_state(Entities::Characters::top);
            one->set_collide_state(Entities::Characters::ground);
            other->set_position(other->get_position().x, other->get_position().y - (intersect_y));
            one->set_position(one->get_position().x, one->get_position().y + (intersect_y));
            dir_one.y = 0.0f;
            dir_other.y = 0.0f;
        } else {
            other->set_collide_state(Entities::Characters::ground);
            one->set_collide_state(Entities::Characters::top);
            other->set_position(other->get_position().x, other->get_position().y + (intersect_y));
            one->set_position(one->get_position().x, one->get_position().y - (intersect_y));
            dir_one.y = 0.0f;
            dir_other.y = 0.0f;
        }
    }
}



void CollisionManager::collision_control(Entities::Characters::Player *other) {
    // verify collision with all objects

    for (int i = 0; i < this->obstacles.getLen(); i++) {
        auto obstacle = this->obstacles.getItem(i);
        // player collision with obstacles
        if (this->check_collision(*obstacle, *other)) {
            if (obstacle->get_type() != "coin") {
                this->update_intersects_obstacle_character(obstacle, other, other->get_velocity(), true);
            } else if(obstacle->get_type() == "coin") {
                obstacles.pop(obstacle);
            }
            other->on_collision(obstacle->get_type());
        }

        // enemies collision with obstacles
        for (auto &enemy : this->enemies) {
            if (obstacle->get_type() != "coin") { // remove coin from obstacle types that enemy can collide
                if (this->check_collision(*obstacle, *enemy)) {
                    this->update_intersects_obstacle_character(obstacle, enemy, enemy->get_velocity(), true);
                    enemy->on_collision(obstacle->get_type());
                }
            }
        }
    }

    // verify collision between characters, enemies vs player
    for (auto &enemy : this->enemies) {
        if (this->check_collision(*enemy, *other)) {
            this->update_intersects_characters(enemy, other, other->get_velocity(), enemy->get_velocity());
            other->on_collision(enemy->get_type());
            enemy->on_collision(other->get_type());
        }
    }
}

