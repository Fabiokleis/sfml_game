#include "level2.hpp"
using namespace Levels;

Level2::Level2() : Level(), coin_tex(), spike_tex() {

}

Level2::Level2(Managers::GraphicManager *graphic_manager, const std::string &map_name, float* pDeltaT)
        : Level(graphic_manager, map_name, pDeltaT), coin_tex(), spike_tex()
{
    this->build_level();
}

Level2::~Level2() {
    delete coin_tex;
    delete spike_tex;
}

void Level2::init_textures() {
    this->coin_tex = new sf::Texture();
    this->spike_tex = new sf::Texture();
}

void Level2::build_level() {
    this->init_textures();
    this->generate_instances();
    this->generate_sizes();
    this->arbritary_positions();
}

void Level2::update() {
    if ((this->platforms.getItem(0)->get_position().y + this->platforms.getItem(0)->get_size().y) < this->height) {
        for (int i = 0; i < this->platforms.getLen(); i++) {
            auto plat = this->platforms.getItem(i);
            plat->move(0, this->gravity + 200.0f);
            if (plat->get_position().y >= (this->height - plat->get_size().y)) {
                plat->set_position(plat->get_position().x + (plat->get_size().x/2.0f),plat->get_position().y);
                plat->set_origin(plat->get_size().x / 2.0f, plat->get_size().y / 2.0f);
            }
        }
    }
    if ((this->walls.getItem(0)->get_position().y + this->walls.getItem(0)->get_size().y) < this->height) {
        for (int i = 0; i < this->walls.getLen(); i++) {
            auto wall = this->platforms.getItem(i);
            wall->move(0, this->gravity + 50.0f);
            if (wall->get_position().y >= (this->height - wall->get_size().y)) {
                wall->set_position(wall->get_position().x + (wall->get_size().x / 2.0f), wall->get_position().y);
                wall->set_origin(wall->get_size().x / 2.0f, wall->get_size().y / 2.0f);
            }
        }
    }

    if ((this->spikes.getItem(0)->get_position().y + this->spikes.getItem(0)->get_size().y) <= (this->platforms.getItem(0)->get_position().y - this->platforms.getItem(0)->get_size().y)) {
        for (int i = 0; i < this->spikes.getLen(); i++) {
            auto spike = this->spikes.getItem(i);
            auto plat = this->platforms.getItem(i);
            spike->move(0, this->gravity + 50.0f);
            if (spike->get_position().y >= (plat->get_position().y - plat->get_size().y)) {
                spike->set_position(spike->get_position().x + 16, plat->get_position().y - (plat->get_size().y/2 + 16));
                spike->set_origin(spike->get_size().x / 2.0f, spike->get_size().y / 2.0f);
            }
        }
    }
}


void Level2::generate_instances() {

    this->platforms_number = generate_random(15, 20);
    for (int i = 0; i < this->platforms_number; i++) {
        this->platforms.push(new Entities::Obstacles::Platform());
        auto plat = this->platforms.getItem(i);
        plat->set_color(sf::Color::Blue);
        plat->set_out_color(sf::Color::Yellow);
        plat->set_graphic_manager(get_render());
        ListaEnti.LEs.push(plat);
    }

    this->walls_number = generate_random(10, 15);
    for (int i = 0; i < this->walls_number; i++) {
        this->walls.push(new Entities::Obstacles::Wall());
        auto wall = this->walls.getItem(i);
        wall->set_color(sf::Color::Black);
        wall->set_out_color(sf::Color::White);
        wall->set_graphic_manager(get_render());
        ListaEnti.LEs.push(wall);
    }


    this->spikes_number = generate_random(10, 15);
    for (int i = 0; i < this->spikes_number; i++) {
        this->spikes.push(new Entities::Obstacles::Spike(this->get_render(), this->spike_tex, 0, 0, 32, 32, SPIKE_PATH));
        auto spike = this->spikes.getItem(i);
        spike->set_graphic_manager(get_render());
        ListaEnti.LEs.push(spike);
    }


    this->coins_number = generate_random(20, 30);
    for (int i = 0; i < this->coins_number; i++) {
        this->coins.push(new Entities::Obstacles::Coin(this->get_render(), this->coin_tex, COIN_PATH, i, 0, 0, 32, 32));
        auto coin = this->coins.getItem(i);
        coin->set_graphic_manager(get_render());
        ListaEnti.LEs.push(coin);
    }
}

void Level2::generate_sizes() {

    for (int i = 0; i < this->platforms.getLen(); i++) {
        auto plat = this->platforms.getItem(i);
        plat->set_size(generate_random(200, 720), generate_random(96, 128));
    }

    for (int i = 0; i < this->walls.getLen(); i++) {
        auto wall = this->walls.getItem(i);
        wall->set_size(32, generate_random(128, 175));
    }
}

void Level2::arbritary_positions() {

    int distrSpaceP = generate_random(4, 7); // space between two platforms
    Entities::Obstacles::Platform aux_p;
    float i = 0;
    float p = 0;
    for (int a = 0; a < this->platforms.getLen(); a++) {
        auto plat = this->platforms.getItem(a);
        plat->set_position((aux_p.get_position().x + aux_p.get_size().x + (i * 32)) * p, plat->get_position().y);
        i = distrSpaceP;
        p = 1;
        aux_p = *plat;
    }

    // generate a position to wall
    for (int u = 0; u < this->walls.getLen(); u++) {
        auto plat = this->platforms.getItem(u);
        auto wall = this->walls.getItem(u);
        int distrSpaceW = generate_random(128, (plat->get_size().x - 32)); // the local of wall
        float space = (distrSpaceW + plat->get_position().x);
        wall->set_position(space, wall->get_position().y - plat->get_size().y);
    }

    // generate a position to spikes
    for (int s = 0; s < this->spikes.getLen(); s++) {
        auto spike = this->spikes.getItem(s);
        auto plat = this->platforms.getItem(s);
        int distrSpaceS = generate_random(64, 128);
        float space = (distrSpaceS + plat->get_position().x);
        spike->set_position(space, spike->get_position().y - plat->get_size().y);
    }
    // generate a position to coins
    Entities::Obstacles::Coin aux_c;
    int prop = ceil(this->coins_number / this->platforms_number);
    std::cout << "prop: " << prop << "tm: " << this->coins_number << std::endl;
    int c_ = 0;
    for (int pp = 0; pp < this->platforms_number; pp++) {
        for (int c = 0; c < prop; c++) {
            auto coin = this->coins.getItem(c_);
            auto plat = this->platforms.getItem(pp);
            coin->set_position(aux_c.get_position().x + generate_random(256, 512), this->height - plat->get_size().y - (generate_random(160, 192)));
            aux_c = *coin;
            c_++;
        }
    }
}
