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
    for(int i = ListaDungas.getLen()-1; i >= 0; i--) {
        ListaDungas.pop(ListaDungas.getItem(i));
    }
    for(int i = ListaEnti.LEs.getLen()-1; i >= 0; i--) {
        ListaEnti.LEs.pop(ListaEnti.LEs.getItem(i));
    }
}

// render order of level
void Level::render() {
    this->get_render()->render(this->sprite);

    for (auto &wall : this->walls) {
//        this->get_render()->render(wall.get_sprite());
        wall.render();
    }
    for (auto &plat : this->platforms) {
        plat.render();
    }

    for (auto &spike : this->spikes) {
        spike.render();
    }
    for (auto &coin : this->coins) {
        coin.render();
    }
    //for(auto &dunga: this->dungas){
    //    dunga.render();
    //}
    for(int i = 0; i < ListaDungas.getLen(); i++){
        ListaDungas.getItem(i)->render();
        std::cout << ListaDungas.getItem(i)->get_position().x << std::endl;
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

void Level::collision_manager(Entities::Player *other) {

    if (other->get_position().x == this->width) {
        // verify if other collide with the end of level, to load next level
    }

    if (ListaDungas.getLen() > 0) {
        for (int i = 0; i < ListaDungas.getLen(); i++) {
            Entities::Characters::Dunga *temp = ListaDungas.getItem(i);
            if(temp->get_collider().check_collision(other->get_collider(), other->get_velocity(), true)){
                other->on_collision(temp->get_type(), temp->get_collide_state());
                temp->on_collision("player");
                if(temp->get_collide_state() == Entities::top){
                    temp->set_state(Entities::dead);
                    temp->update_life_number();
                    ListaDungas.pop(temp);
                }
            }
        }
    }
    /*if (!this->dungas.empty()) {
        for (auto &dunga: this->dungas) {
            if (dunga.get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
                other->on_collision(dunga.get_type(), dunga.get_collide_state());
                if(dunga.get_collide_state() == Entities::top){
                    dunga.set_state(Entities::dead);
                    dunga.update_life_number();
                    this->dungas.erase(std::remove_if(this->dungas.begin(), this->dungas.end(), [&dunga](const Entities::Characters::Dunga& dunga_aux) {
                                                          return dunga.get_id() == dunga_aux.get_id();}), this->dungas.end());
                }
            }
        }
    }*/


    // platforms and other collision
    for (auto &platform: this->platforms) {
        if (platform.get_collider().check_collision(other->get_collider(), other->get_velocity(),true))
        {
            other->on_collision(platform.get_type());
        }
        for(int i = 0; i < ListaDungas.getLen(); i++){
            auto *temp = ListaDungas.getItem(i);
            if (platform.get_collider().check_collision(temp->get_collider(), temp->get_velocity(),true))
            {
                other->on_collision(platform.get_type());
            }
        }
    }
    // walls and other collision
    for (auto &wall: this->walls) {
        if (wall.get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
            other->on_collision(wall.get_type());
        }
        for(int i = 0; i < ListaDungas.getLen(); i++){
            auto *temp = ListaDungas.getItem(i);
            if (wall.get_collider().check_collision(temp->get_collider(), temp->get_velocity(),true))
            {
                other->on_collision(wall.get_type());
            }
        }
    }
    // spikes and other collision
    for (auto &spike: this->spikes) {
        if (spike.get_collider().check_collision(other->get_collider(), other->get_velocity(), true)) {
            other->on_collision(spike.get_type());
        }
        for(int i = 0; i < ListaDungas.getLen(); i++){
            auto *temp = ListaDungas.getItem(i);
            if (spike.get_collider().check_collision(temp->get_collider(), temp->get_velocity(),true))
            {
                temp->on_collision(spike.get_type());
            }
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

ListaEntidades* Level::get_lista_entidades() {
    return &ListaEnti;
}

sf::RectangleShape Level::get_sprite() const {
    return this->sprite;
}
