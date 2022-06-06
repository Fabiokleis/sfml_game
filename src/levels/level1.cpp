#include "level1.hpp"
using namespace Levels;

Level1::Level1() : Level(), coin_tex(), spike_tex() {}

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

    this->platforms_number = generate_random(15, 20);
    for (int i = 0; i < this->platforms_number; i++) {
        this->platforms.emplace_back(Entities::Platform());
        this->platforms[i].set_color(sf::Color::Blue);
        this->platforms[i].set_out_color(sf::Color::Yellow);
    }

    this->walls_number = generate_random(7, 15); // define the range
    for (int i = 0; i < this->walls_number; i++) {
        this->walls.emplace_back(Entities::Wall());
        this->walls[i].set_color(sf::Color::Black);
        this->walls[i].set_out_color(sf::Color::White);
    }

    this->spikes_number = generate_random(7, 15);
    for (int i = 0; i < this->spikes_number; i++) {
        this->spikes.emplace_back(this->get_render(), this->spike_tex, 0, 0, 32, 32, SPIKE_PATH);
    }

    this->coins_number = generate_random(45, 60);
    for (int i = 0; i < this->coins_number; i++) {
        this->coins.emplace_back(this->get_render(), this->coin_tex, COIN_PATH, i, 0, 0, 32, 32);
    }
}

void Level1::generate_sizes() {

    for (auto &plat : this->platforms) {
        plat.set_size(generate_random(256, 512), generate_random(96, 128));
    }

    for (auto &wall : this->walls) {
        wall.set_size(32, generate_random(128, 170));
    }
}

void Level1::arbritary_positions() {

    int distrSpaceP = generate_random(2, 4); // space between two platforms
    Entities::Platform aux_p;
    float i = 0;
    float p = 0;
    for (auto &plat: this->platforms) {
        plat.set_position((aux_p.get_position().x + aux_p.get_size().x + (i * 32)) * p, plat.get_position().y);
        i = distrSpaceP;
        p = 1;
        aux_p = plat;
    }

    // generate a position to wall
    for (int u = 0; u < this->walls_number; u++) {
        float plat_sx = this->platforms[u].get_size().x;
        int distrSpaceW = generate_random(128, (plat_sx - 64)); // the local of wall
        float space = (distrSpaceW + this->platforms[u].get_position().x);
        this->walls[u].set_position(space, this->walls[u].get_position().y - this->platforms[u].get_size().y);
    }

    // generate a position to spikes
    for (int s = 0; s < this->spikes_number; s++) {
        int distrSpaceS = generate_random(64, 128);
        float space = (distrSpaceS + this->platforms[s].get_position().x);
        this->spikes[s].set_position(space, this->spikes[s].get_position().y - this->platforms[s].get_size().y);
    }

    // generate a position to coins
    Entities::Coin aux_c;
    int prop = ceil(this->coins_number / this->platforms_number);
    std::cout << "prop: " << prop << "tm: " << this->coins_number << std::endl;
    int c_ = 0;
    for (int pp = 0; pp < this->platforms_number; pp++) {
        for (int c = 0; c < prop; c++) {
            float plat_sy = this->platforms[pp].get_size().y;
            this->coins[c_].set_position(aux_c.get_position().x + generate_random(128, 160), this->height - plat_sy - (generate_random(128, 160)));
            aux_c = this->coins[c_];
            c_++;
        }
    }
}

void Level1::init_textures() {
    this->coin_tex = new sf::Texture();
    this->spike_tex = new sf::Texture();
}