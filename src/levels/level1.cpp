#include "level1.hpp"
using namespace Levels;

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
    if ((this->walls.getItem(0)->get_position().y) < this->height) {
        for (int i = 0; i < this->walls.getLen(); i++) {
            auto wall = this->walls.getItem(i);
            wall->move(0, this->gravity + 100.0f);
            if (wall->get_position().y >= (this->height - wall->get_size().y)) {
                wall->set_position(wall->get_position().x, wall->get_position().y);
                wall->set_origin(wall->get_size().x / 2.0f, wall->get_size().y / 2.0f);
            }
        }
    }

    if ((this->spikes.getItem(0)->get_position().y) <= (this->platforms.getItem(0)->get_position().y - this->platforms.getItem(0)->get_size().y)) {
        for (int i = 0; i < this->spikes.getLen(); i++) {
            auto spike = this->spikes.getItem(i);
            auto plat = this->platforms.getItem(i);
            spike->move(0, this->gravity + 100.0f);
            if (spike->get_position().y >= (plat->get_position().y - plat->get_size().y)) {
                spike->set_position(spike->get_position().x + 16, plat->get_position().y - (plat->get_size().y/2 + 16));
                spike->set_origin(spike->get_size().x / 2.0f, spike->get_size().y / 2.0f);
            }
        }
    }

    for(int i = 0; i < this->ListaEnti.LEs.getLen(); i++){
        this->ListaEnti.LEs.getItem(i)->update();
    }
}

void Level1::generate_instances() {
    this->walls_number = generate_random(10, 15); // define the range
    for (int i = 0; i < this->walls_number; i++) {
        auto wall = new Entities::Obstacles::Wall(this->get_render(), 0, 0, 0, 0, sf::Color::Black);
        wall->set_out_color(sf::Color::White);
        this->walls.push(wall);
        this->obstacles.push(static_cast<Entities::Obstacles::Obstacle*>(wall));
        ListaEnti.LEs.push(wall);
    }

    this->platforms_number = generate_random(15, 18);
    for (int i = 0; i < this->platforms_number; i++) {
        auto t_plat = new Entities::Obstacles::Platform(this->get_render(), 0, 0, 0, 0, sf::Color::Blue);
        t_plat->set_out_color(sf::Color::Yellow);
        this->platforms.push(t_plat);
        this->obstacles.push(static_cast<Entities::Obstacles::Obstacle*>(t_plat));
        ListaEnti.LEs.push(t_plat);
    }

    this->spikes_number = generate_random(10, 15);
    for (int i = 0; i < this->spikes_number; i++) {
        auto spike = new Entities::Obstacles::Spike(this->get_render(), this->spike_tex, 0, 0, 32, 32, SPIKE_PATH);
        this->spikes.push(spike);
        this->obstacles.push(static_cast<Entities::Obstacles::Obstacle*>(spike));
        ListaEnti.LEs.push(spike);
    }

    this->coins_number = generate_random(20, 30);
    for (int i = 0; i < this->coins_number; i++) {
        auto coin = new Entities::Obstacles::Coin(this->get_render(), this->coin_tex, COIN_PATH, 0, 0, 32, 32);
        this->coins.push(coin);
        this->obstacles.push(static_cast<Entities::Obstacles::Obstacle*>(coin));
        ListaEnti.LEs.push(coin);
    }

    this->dungas_number = generate_random(5, 8);
    for (int i = 0; i < this->dungas_number; i++) {
        auto *temp = new Entities::Characters::Dunga(i, this->get_render(), 45, 45, 0, 0,
                                                                            1, sf::Vector2u (2,1), 0.2, Entities::Characters::idle,
                                                                            DUNGA_PATH, &Managers::GraphicManager::delta_time);
        this->dungas.push(temp);
        this->enemies.push_back(temp);
        ListaEnti.LEs.push(temp);
    }

    this->zezinho_number = generate_random(3, 5);
    for (int i = 0; i < this->zezinho_number; i++) {
        auto *temp = new Entities::Characters::Zezinho(i+this->dungas_number, this->get_render(), 46, 62, 0, 0,
                                                     1, sf::Vector2u (8,2), 0.07, Entities::Characters::idle,
                                                     ZE_PATH, &Managers::GraphicManager::delta_time, player);
        this->listaZe.push(temp);
        this->enemies.push_back(temp);
        ListaEnti.LEs.push(temp);
    }
}

void Level1::generate_sizes() {

    for (int i = 0; i < this->platforms.getLen(); i++) {
        auto plat = this->platforms.getItem(i);
        plat->set_size(generate_random(400, 580), generate_random(96, 128));
    }

    for (int i = 0; i < this->walls.getLen(); i++) {
        auto wall = this->walls.getItem(i);
        wall->set_size(32, generate_random(412, 448));
    }
}

void Level1::arbritary_positions() {

    int distrSpaceP = generate_random(2, 4); // space between two platforms
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
    for (int u = 0, p = 1; u < this->walls.getLen(); u++, p++) {
        auto plat = this->platforms.getItem(p);
        auto wall = this->walls.getItem(u);
        int distrSpaceW = generate_random((plat->get_size().x - (plat->get_half_size().x - (plat->get_half_size().x/2.0f))), (plat->get_size().x - 96)); // the local of wall
        float space = (distrSpaceW + plat->get_position().x);
        wall->set_position(space, 0.0f);
    }

    // generate a position to spikes
    for (int s = 0; s < this->spikes.getLen(); s++) {
        auto spike = this->spikes.getItem(s);
        auto plat = this->platforms.getItem(s);
        int distrSpaceS = generate_random(72, 96);
        float space = (distrSpaceS + plat->get_position().x);
        spike->set_position(space, 0.0f);
    }

    // generate a position to coins
    Entities::Obstacles::Coin aux_c;
    int prop = ceil(this->coins_number / this->platforms_number);
    int c_ = 0;
    for (int pp = 0; pp < this->platforms_number; pp++) {
        for (int c = 0; c < prop; c++) {
            auto coin = this->coins.getItem(c_);
            auto plat = this->platforms.getItem(pp);
            coin->set_position(aux_c.get_position().x + generate_random(128, 160), this->height - plat->get_size().y - (generate_random(128, 160)));
            aux_c = *coin;
            c_++;
        }
    }

    //generate a position to dungas
    for (int s = 0, p = 1; s < this->dungas_number; s++, p++) {
        int distrSpaceS = generate_random(192, 256);
        auto plat = this->platforms.getItem(p);
        float space = (distrSpaceS + plat->get_position().x);
        this->dungas.getItem(s)->set_position(space, 600);
    }

    //generate a position to zes
    for (int s = 0, p = 3; s < this->zezinho_number; s++, p++) {
        int distrSpaceS = generate_random(192, 256);
        auto plat = this->platforms.getItem(p);
        float space = (distrSpaceS + plat->get_position().x);
        this->listaZe.getItem(s)->set_position(space, 400);
    }
}

void Level1::init_textures() {
    this->coin_tex = new sf::Texture();
    this->spike_tex = new sf::Texture();
}