#include <iostream>
#include <fstream>
#include "level.hpp"
#include "config.h"
using namespace Levels;


Level::Level() : height(), width(), tile_height(), tile_width(), background() {}

Level::Level(Managers::GraphicManager *graphic_manager, const std::string& map_name) :
    Entie(graphic_manager), height(), width(), tile_height(), tile_width(), background()
{
    this->init_variables();
}

Level::~Level() {}

void Level::init_variables() {

}

void Level::update() {

}

// render order of level
void Level::render() {
    this->background->render();
}


int Level::get_height() const {
    return this->height;
}

int Level::get_width() const {
    return this->width;
}

int Level::get_tile_width() const {
    return this->tile_width;
}

int Level::get_tile_height() const {
    return this->tile_height;
}

std::string Level::get_name() {
    return this->map_name;
}

// read a file and returns
std::string Level::read_file(const std::string& filename) {
    std::cout << filename << "\n";
    std::ostringstream buf;
    std::ifstream input(filename.c_str());
    buf << input.rdbuf();
    std::cout << buf.str();
    return buf.str();
}

void Level::collision_manager(Entities::Player *other) {

//    if (this->end_location.get_collider().check_collision(other->get_collider(), other->get_velocity(), false)) {
//        // verify if jaime collide with the end of level, to load next level
//        this->next_map();
//    }
//    for (auto &check_point : this->check_points) {
//        if (check_point.get_collider().check_collision(other->get_collider(), other->get_velocity(), false)) {
//            // verify if jaime collide with check point to save the game
//            this->save_game(check_point);
//        }
//    }
//
//    // platform and jaime collision
//    for (auto &platform: this->platforms->get_platforms()) {
//        if (platform.get_collider().check_collision(other->get_collider(), other->get_velocity(),true))
//        {
//            other->on_collision(platform.get_type());
//        }
//    }
//    // walls and jaime collision
//    for (auto &wall: this->walls->get_walls()) {
//        if (wall.get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
//            other->on_collision(wall.get_type());
//        }
//    }
//    // tiles and jaime collision, set a different collision by type
//    for (auto &tile: this->tiles->get_tiles()) {
//
//        if (tile.get_type() == "coin" && !this->coins.empty()) {
//            if (tile.get_collider().check_collision(other->get_collider(), other->get_velocity(),false)) {
//                for (auto coin = this->coins.cbegin(); coin < this->coins.cend(); *coin++) {
//                    // if coin id is equal tile id, then increment jaime score and erase from coins after testing collision
//                    if (coin->get_id() == tile.get_id()) {
//                        coin = this->coins.erase(coin);
//                        other->on_collision(tile.get_type());
//                    }
//                }
//            }
//        }
//
//        if (tile.get_type() == "spike" ) {
//            if (tile.get_collider().check_collision(other->get_collider(),other->get_velocity(),
//                                                    true)) {
//                if (other->get_state() != Entities::dead) {
//                    other->on_collision(tile.get_type());
//                }
//            }
//        }
//
//        if (tile.get_type() == "block") {
//            if (tile.get_collider().check_collision(other->get_collider(), other->get_velocity(),
//                                                    true)) {
//                other->on_collision(tile.get_type());
//            }
//        }
//    }
}