#include <iostream>
#include <fstream>
#include "level.hpp"
#include "config.h"
using namespace Levels;

std::random_device rd; // get random number from hardware
std::mt19937 gen(rd()); // seed generator

Level::Level(Managers::GraphicManager *graphic_manager,  std::string map_name) :
    Entie(graphic_manager), x(0), y(0), platforms_number(0), walls_number(0),
    coins_number(0), spikes_number(0), dungas_number(0), map_name(map_name), gravity(9.81f),
    collision_manager(this->obstacles, this->enemies)
{
    this->sprite.setPosition(static_cast<float>(x), static_cast<float>(y)); // default top 0 and left 0 cords
    this->load_texture();
    this->sprite.setTexture(&this->texture);
    this->sprite.setSize(sf::Vector2f(this->texture.getSize().x, this->texture.getSize().y));
    this->width = this->texture.getSize().x;
    this->height = this->texture.getSize().y;
}

Level::~Level() {

    for(int i = this->obstacles.getLen()-1; i >= 0; i--) {
        this->obstacles.pop(this->obstacles.getItem(i));
    }

    for(int i = ListaEnti.LEs.getLen()-1; i >= 0; i--) {
        ListaEnti.LEs.pop(ListaEnti.LEs.getItem(i));
    }
}

// render order of level
void Level::render() {
    this->get_render()->render(this->sprite);
//    for (int i = 0; i < this->ListaEnti.LEs.getLen(); i++) {
//        ListaEnti.LEs.getItem(i)->render();
//    }

    // render all obstacles from levels
    for (int i = 0; i < this->obstacles.getLen(); i++) {
        obstacles.getItem(i)->render();
    }
    for (auto enemy : this->enemies) {
        enemy->render();
    }
//    for (int i = 0; i < this->ListaEnti.LEs.getLen(); i++) {
//        auto t_obs = this->ListaEnti.LEs.getItem(i);
//        t_obs->render();
//    }

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

// read a file and returns a buffer
std::string Level::read_file(const std::string& filename) {
    std::cout << filename << "\n";
    std::ostringstream buf;
    std::ifstream input(filename.c_str());
    buf << input.rdbuf();
    std::cout << buf.str();
    return buf.str();
}

void Level::handle_collision(Entities::Characters::Player *other) {
    this->collision_manager.collision_control(other);

}

void Level::load_texture() {
    std::string assets_path = RESOURCE_PATH;
    std::cout << std::endl << assets_path + this->map_name << std::endl;
    if (!this->texture.loadFromFile(assets_path+this->map_name)) {
        std::cout << "ERROR::LEVEL_TEXTURE:: COULD NOT LOAD TEXTURE FILE." << std::endl;
    }
}

Listas::ListaEntidades* Level::get_lista_entidades() {
    return &ListaEnti;
}

void Level::set_player(Entities::Characters::Player *player) {
    this->player = player;
    for(int i = 0; i < listaZe.getLen(); i++){
        listaZe.getItem(i)->set_player(player);
    }
    for(int i = 0; i < listaRammus.getLen(); i++){
        listaRammus.getItem(i)->set_player(player);
    }
}
