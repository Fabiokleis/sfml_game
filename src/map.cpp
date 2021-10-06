#include "map.hpp"
#include "tile.hpp"

Map::Map() {
    this->grid_size_f = 16;
    this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
    this->max_size.x = 50;
    this->max_size.y = 40;
    this->layers = 1;

    this->map.resize(this->max_size.x);

    for (size_t x = 0; x < this->max_size.x; x++) {

        this->map.push_back(std::vector<std::vector<Tile*>>());

        for (size_t y = 0; y < this->max_size.y; y++) {

            this->map[x].resize(max_size.y);
            this->map[x].push_back(std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++) {

                this->map[x][y].resize(this->layers);
                this->map[x][y].push_back(
                    new Tile(
                        x * this->grid_size_f, 
                        y * this->grid_size_f,
                        this->grid_size_f
                    )
                );
            }
        }
    }
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

void Map::update() {

}

void Map::render(sf::RenderTarget* target) {
    for (auto &x : this->map) {
        for (auto &y : x) {
            for (auto *z : y) {
                if (z != nullptr)
                    z->render(target);
            }
        }
    }
}