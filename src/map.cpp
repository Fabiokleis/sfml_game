#include <iostream>
#include "config.h"
#include "map.hpp"
#include "tile.hpp"


Map::Map(const float grid, const unsigned max_x, const unsigned max_y) {
    this->grid_size_f = grid;
    this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
    this->max_size.x = max_x;
    this->max_size.y = max_y;
    this->layers = 1;

    this->map.resize(this->max_size.x, std::vector<std::vector<Tile*>>());

    for (size_t x = 0; x < this->max_size.x; x++) {

        for (size_t y = 0; y < this->max_size.y; y++) {

            this->map[x].resize(max_size.y, std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++) {

                this->map[x][y].resize(this->layers, NULL
                    // new Tile(
                    //     x * this->grid_size_f, 
                    //     y * this->grid_size_f,
                    //     this->grid_size_f
                    // )
                );
            }
        }
    }
    // std::string path = RESOURCE_PATH;
    // this->tile_texture_sheet = new sf::Texture();
    // if(!this->tile_texture_sheet->loadFromFile(path+"map/EmptyBlock.png")) {
    //     std::cout << "ERROR:MAP::FAILED TO LOAD TEXTURESHEET." << std::endl;
    // }
}

Map::~Map() {
    for (size_t x = 0; x < this->max_size.x; x++) {
        for (size_t y = 0; y < this->max_size.y; y++) {
            for (size_t z = 0; z < this->layers; z++) {
                delete this->map[x][y][z];
            }
        }
    }
}

void Map::add_tile(const unsigned x, const unsigned y, const unsigned z) {

    if (
        x < this->max_size.x && x >= 0 &&
        y < this->max_size.y && y >= 0 &&
        z < this->layers && z >= 0) {

        if (this->map[x][y][z] == NULL) {
            this->map[x][y][z] = new Tile(
                x * this->grid_size_f, 
                y * this->grid_size_f, 
                this->grid_size_f,
                this->tile_texture_sheet
            );
        }
    }
}

void Map::remove_tile(const unsigned x, const unsigned y, const unsigned z) {

    if (
        x < this->max_size.x && x >= 0 &&
        y < this->max_size.y && y >= 0 &&
        z < this->layers && z >= 0) {

        if (this->map[x][y][z] != NULL) {
            delete this->map[x][y][z];
            this->map[x][y][z] = NULL;
        }
    }
}



void Map::update() {

}

void Map::render(sf::RenderTarget* target) {
    for (auto &x : this->map) {
        for (auto &y : x) {
            for (auto *z : y) {
                if (z != NULL)
                    z->render(target);
            }
        }
    }
}