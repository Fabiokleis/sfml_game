#include <iostream>
#include <fstream>
#include "level.hpp"
#include "config.h"
using namespace Levels;

std::random_device rd; // get random number from hardware
std::mt19937 gen(rd()); // seed generator
Level::Level() : x(), y(), sprite(), platforms_number(), walls_number(), spikes_number(), coins_number(), dungas_number(), gravity(), width(), height(), pDeltaT() {}

Level::Level(Managers::GraphicManager *graphic_manager,  std::string map_name, float* pDeltaT) :
    Entie(graphic_manager), x(0), y(0), platforms_number(0), walls_number(0),
    coins_number(0), spikes_number(0), dungas_number(0), map_name(map_name), gravity(9.81f), pDeltaT(pDeltaT)
{
    this->sprite.setPosition(static_cast<float>(x), static_cast<float>(y)); // default top 0 and left 0 cords
    this->load_texture();
    this->sprite.setTexture(&this->texture);
    this->sprite.setSize(sf::Vector2f(this->texture.getSize().x, this->texture.getSize().y));
    this->width = this->texture.getSize().x;
    this->height = this->texture.getSize().y;
}

Level::~Level() {
    for(int i = this->dungas.getLen()-1; i >= 0; i--) {
        this->dungas.pop(this->dungas.getItem(i));
    }
    for(int i = ListaEnti.LEs.getLen()-1; i >= 0; i--) {
        ListaEnti.LEs.pop(ListaEnti.LEs.getItem(i));
    }
}

// render order of level
void Level::render() {
    this->get_render()->render(this->sprite);

    for (int i = 0; i < this->ListaEnti.LEs.getLen(); i++) {
        auto t_obs = this->ListaEnti.LEs.getItem(i);
        t_obs->render();
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

// generate a random number between lower and higher range
int Level::generate_random(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(gen);
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

void Level::collision_manager(Entities::Characters::Player *other) {

    if (other->get_position().x == this->width) {
        // verify if other collide with the end of level, to load next level
    }

    if (this->dungas.getLen() > 0) {
        for (int i = 0; i < this->dungas.getLen(); i++) {
            Entities::Characters::Dunga *temp = this->dungas.getItem(i);
            if(temp->get_collider().check_collision(other->get_collider(), other->get_velocity(), true)){
                temp->on_collision("player");
                other->on_collision(temp->get_type(), temp->get_collide_state());
                if(temp->get_collide_state() == Entities::Characters::top){
                    temp->set_state(Entities::Characters::dead);
                    temp->update_life_number();
                    this->dungas.pop(temp);
                    this->ListaEnti.LEs.pop(temp);
                }
            }
        }
    }

    // platforms and other collision

    for (int i = 0; i < this->platforms.getLen(); i++) {
        Entities::Obstacles::Platform *platform = this->platforms.getItem(i);
        if (platform->get_collider().check_collision(other->get_collider(), other->get_velocity(),true))
        {
            other->on_collision(platform->get_type());
        }
        for(int i = 0; i < this->dungas.getLen(); i++){
            auto *temp = this->dungas.getItem(i);
            if (platform->get_collider().check_collision(temp->get_collider(), temp->get_velocity(),true))
            {
                other->on_collision(platform->get_type());
            }
        }
    }
    // walls and other collision
    for (int i = 0; i < this->walls.getLen(); i++) {
        Entities::Obstacles::Wall *wall = this->walls.getItem(i);
        if (wall->get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
            other->on_collision(wall->get_type());
        }
        for(int i = 0; i < this->dungas.getLen(); i++){
            auto *temp = this->dungas.getItem(i);
            if (wall->get_collider().check_collision(temp->get_collider(), temp->get_velocity(),true))
            {
                other->on_collision(wall->get_type());
            }
        }
    }
    // spikes and other collision
    for (int i = 0; i < this->spikes.getLen(); i++) {
        Entities::Obstacles::Spike *spike = this->spikes.getItem(i);
        if (spike->get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
            other->on_collision(spike->get_type());
        }
        for(int i = 0; i < this->dungas.getLen(); i++){
            auto *temp = this->dungas.getItem(i);
            if (spike->get_collider().check_collision(temp->get_collider(), temp->get_velocity(),true))
            {
                temp->on_collision(spike->get_type());
            }
        }
    }
    // coins and other collision
    if (this->coins.getLen() > 0) {
        for (int i = 0; i < this->coins.getLen(); i++) {
            Entities::Obstacles::Coin *coin = this->coins.getItem(i);
            if (coin->get_collider().check_collision(other->get_collider(), other->get_velocity(), false)) {
                other->on_collision(coin->get_type());

                this->coins.pop(coin);
                this->ListaEnti.LEs.pop(coin);
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

ListaEntidades* Level::get_lista_entidades() {
    return &ListaEnti;
}

sf::RectangleShape Level::get_sprite() const {
    return this->sprite;
}
