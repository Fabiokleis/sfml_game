#include "level1.hpp"
#include <random>
using namespace Levels;

Level1::Level1() : Level() {}

Level1::Level1(Managers::GraphicManager *graphic_manager, const std::string &map_name)
        : Level(graphic_manager, map_name), coin_tex(), spike_tex()
{
    this->build_level();
}

Level1::~Level1() {
    delete coin_tex;
    delete spike_tex;
}

void Level1::build_level() {
    this->init_textures();
    this->generate_instances();
    this->generate_sizes();
    this->arbritary_positions();
}

void Level1::update() {
    if ((this->platforms[0].get_position().y + this->platforms[0].get_size().y) < this->height) {
        for (auto &plat: this->platforms) {
            plat.move(0, this->gravity + 200.0f);
            if (plat.get_position().y >= (this->height - plat.get_size().y)) {
                plat.set_position(plat.get_position().x + (plat.get_size().x/2.0f),plat.get_position().y);
                plat.set_origin(plat.get_size().x / 2.0f, plat.get_size().y / 2.0f);
            }
        }
    }
    if ((this->walls[0].get_position().y + this->walls[0].get_size().y) < this->height) {
        for (auto &wall: this->walls) {
            wall.move(0, this->gravity + 50.0f);
            if (wall.get_position().y >= (this->height - wall.get_size().y)) {
                wall.set_position(wall.get_position().x + (wall.get_size().x / 2.0f), wall.get_position().y);
                wall.set_origin(wall.get_size().x / 2.0f, wall.get_size().y / 2.0f);
            }
        }
    }

    if ((this->spikes[0].get_position().y + this->spikes[0].get_size().y) <= (this->platforms[0].get_position().y - this->platforms[0].get_size().y)) {
        std::cout << "no loop\n";
        for (int s = 0; s <= this->spikes_number; s++) {
            this->spikes[s].move(0, this->gravity + 50.0f);
            if (this->spikes[s].get_position().y >= (this->platforms[s].get_position().y - this->platforms[s].get_size().y)) {
                this->spikes[s].set_position(this->spikes[s].get_position().x + 16, this->platforms[s].get_position().y - (this->platforms[s].get_size().y/2 + 16));
                this->spikes[s].set_origin(this->spikes[s].get_size().x / 2.0f, this->spikes[s].get_size().y / 2.0f);
            }
        }
    }
}

void Level1::generate_instances() {
    // generate random numbers between ranges following c++ specification
    std::random_device rd; // get random number from hardware
    std::mt19937 gen(rd()); // seed generator
    std::uniform_int_distribution<> distrP(30, 60); // define the range
    this->platforms_number = distrP(gen);

    // populate the platforms vector with a random number of instances 10-20
    for (int i = 0; i < this->platforms_number; i++) {
        this->platforms.emplace_back(Entities::Platform());
        this->platforms[i].set_color(sf::Color::Blue);
        this->platforms[i].set_out_color(sf::Color::Yellow);
    }

    std::uniform_int_distribution<> distrW(10, 15); // define the range
    this->walls_number = distrW(gen);
    // populate the walls vector with a random number of instances 5-10
    for (int i = 0; i < this->walls_number; i++) {
        this->walls.emplace_back(Entities::Wall());
        this->walls[i].set_color(sf::Color::Black);
        this->walls[i].set_out_color(sf::Color::White);
    }

    std::uniform_int_distribution<> distrS(10, 15); // define the range
    this->spikes_number = distrS(gen);
    for (int i = 0; i < this->spikes_number; i++) {
        this->spikes.emplace_back(this->get_render(), this->spike_tex, 0, 0, 32, 32, SPIKE_PATH);
    }
//
//    std::uniform_int_distribution<> distrC(40, 60); // define the range
//    this->coins_number = distrC(gen);
//    // populate the coins vector with a random number of instances 20-40
//    for (int i = 0; i < this->coins_number; i++) {
//        this->coins.emplace_back(this->get_render(), COIN_PATH, i, 0, 0, 32, 32);
//    }
}


void Level1::generate_sizes() {
    // random sizes to obstacles that not uses textures
    std::random_device rd; // get random number from hardware
    std::mt19937 gen(rd()); // seed generator
    std::uniform_int_distribution<> distrSX(192, 512);
    std::uniform_int_distribution<> distrSY(72, 128);
    std::uniform_int_distribution<> distrWSY(128, 160);

    for (auto &plat : this->platforms) {
        plat.set_size(distrSX(gen), distrSY(gen));
    }

    for (auto &wall : this->walls) {
        wall.set_size(32, distrWSY(gen));
    }
}


void Level1::arbritary_positions() {
    std::random_device rd; // get random number from hardware
    std::mt19937 gen(rd()); // seed generator
    std::uniform_int_distribution<> distrSpaceP(2, 4); // space between two platforms
    Entities::Platform aux_p;
    float i = 0;
    float p = 0;
    for (auto &plat : this->platforms) {
        plat.set_position((aux_p.get_position().x + aux_p.get_size().x + (i*32))*p, plat.get_position().y);
        i = distrSpaceP(gen);
        p = 1;
        aux_p = plat;
    }

    // generate a position to wall
    for (int u = 0; u < this->walls_number; u++) {
        float plat_sx = this->platforms[u].get_size().x;
        std::uniform_int_distribution<> distrSpaceW(128, (plat_sx - 64)); // the local of wall
        float space = (distrSpaceW(gen) + this->platforms[u].get_position().x);
        this->walls[u].set_position(space, this->walls[u].get_position().y - this->platforms[u].get_size().y);
    }

    // generate a position to spikes
    for (int s = 0; s < this->spikes_number; s++) {
        float plat_sx = this->platforms[s].get_size().x;
        std::uniform_int_distribution<> distrSpaceW(0, 128); // the local of wall
        float space = (distrSpaceW(gen) + this->platforms[s].get_position().x);
        this->spikes[s].set_position(space, this->spikes[s].get_position().y - this->platforms[s].get_size().y);
    }

    // generate a position to spikes between every platform
//    for (auto &coin : this->coins) {
//
//    }
}

void Level1::init_textures() {
    this->coin_tex = new sf::Texture();
    this->spike_tex = new sf::Texture();
}
