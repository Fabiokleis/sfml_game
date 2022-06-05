#include <iostream>
#include <fstream>
#include "level.hpp"
#include "config.h"
using namespace Levels;


Level::Level() : x(), y(), sprite(), platforms_number(), walls_number(), spikes_number(), coins_number(), gravity() {}

Level::Level(Managers::GraphicManager *graphic_manager,  std::string map_name) :
    Entie(graphic_manager), height(height), width(width), x(0), y(0), platforms_number(0), walls_number(0),
    coins_number(0), spikes_number(0), map_name(map_name), gravity(9.81f)
{
    this->sprite.setPosition(static_cast<float>(x), static_cast<float>(y)); // default top 0 and left 0 cords
    this->load_texture();
    this->sprite.setTexture(&this->texture);
    this->sprite.setSize(sf::Vector2f(this->texture.getSize().x, this->texture.getSize().y));
    this->width = this->texture.getSize().x;
    this->height = this->texture.getSize().y;
}

Level::~Level() {}

// render order of level
void Level::render() {
    this->get_render()->render(this->sprite);

    for (auto &wall : this->walls) {
        this->get_render()->render(wall.get_sprite());
    }
    for (auto &plat : this->platforms) {
        this->get_render()->render(plat.get_sprite());
    }

    for (auto &spike : this->spikes) {
        this->get_render()->render(spike.get_sprite());
    }
    for (auto &coin : this->coins) {
        this->get_render()->render(coin.get_sprite());
    }
}

double Level::get_height() const {
    return this->height;
}

double Level::get_width() const {
    return this->width;
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

    if (other->get_position().x == this->width) {
        // verify if other collide with the end of level, to load next level
    }
    for (auto &check_point : this->check_points) {
        // verify if other collide with check point to save the game
        if (other->get_position().x == check_point) {
            this->save();
        }
    }

    // platforms and other collision
    for (auto &platform: this->platforms) {
        if (platform.get_collider().check_collision(other->get_collider(), other->get_velocity(),true))
        {
            other->on_collision(platform.get_type());
        }
    }
    // walls and other collision
    for (auto &wall: this->walls) {
        if (wall.get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
            other->on_collision(wall.get_type());
        }
    }
    // spikes and other collision
    for (auto &spike: this->spikes) {
        if (spike.get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
            other->on_collision(spike.get_type());
        }
    }
    // coins and other collision
    if (!this->coins.empty()) {
        for (auto &coin: this->coins) {
            if (coin.get_collider().check_collision(other->get_collider(), other->get_velocity(), false)) {
                other->on_collision(coin.get_type());
                this->coins.erase(std::remove_if(this->coins.begin(), this->coins.end(),
                        [&coin](const Entities::Coin& coin_aux) {
                            return coin.get_id() == coin_aux.get_id();
                        }), this->coins.end());
            }
        }
    }
}

void Level::load_texture() {
    std::string assets_path = RESOURCE_PATH;
    std::cout << std::endl << assets_path + this->map_name << std::endl;
    if (!this->texture.loadFromFile(assets_path+this->map_name)) {
        std::cout << "ERROR::LEVEL_TEXTURE:: COULD NOT LOAD TEXTURE FILE." << std::endl;
    }
}

void Level::save() {

}

sf::RectangleShape Level::get_sprite() const {
    return this->sprite;
}
