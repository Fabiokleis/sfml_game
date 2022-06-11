#include "level2.hpp"
using namespace Levels;

Level2::Level2(Managers::GraphicManager *graphic_manager, const std::string &map_name)
        : Level(graphic_manager, map_name), coin_tex(), spike_tex()
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
            spike->move(0, this->gravity + 50.0f);
            if (spike->get_position().y >= (plat->get_position().y - plat->get_size().y)) {
                spike->set_position(spike->get_position().x + 16, plat->get_position().y - (plat->get_size().y/2 + 16));
                spike->set_origin(spike->get_size().x / 2.0f, spike->get_size().y / 2.0f);
            }
        }
    }
    for(int i = 0; i < this->ListaEnti.LEs.getLen(); i++){
        this->ListaEnti.LEs.getItem(i)->update();
    }
    for (int i = 0; i < this->spikes.getLen(); i++) {
        this->spikes.getItem(i)->scale();
    }
}


void Level2::generate_instances() {
    this->walls_number = generate_random(10, 15);
    for (int i = 0; i < this->walls_number; i++) {
        auto wall = new Entities::Obstacles::Wall(this->get_render(),
                                                  0, 0,
                                                  32, generate_random(128, 175), sf::Color(200,70,200,255));
        wall->set_out_color(sf::Color::White);
        this->walls.push(wall);
        this->obstacles.push(static_cast<Entities::Obstacles::Obstacle*>(wall));
        ListaEnti.LEs.push(wall);
    }

    this->platforms_number = generate_random(15, 20);
    for (int i = 0; i < this->platforms_number; i++) {
        auto t_plat = new Entities::Obstacles::Platform(this->get_render(),
                                                        0, 0,
                                                        generate_random(200, 720), generate_random(96, 128), sf::Color(50,50,80,255));
        t_plat->set_out_color(sf::Color(167,167,167,255));
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



    this->zezinho_number = generate_random(5, 7);
    for (int i = 0; i < this->zezinho_number; i++) {
        auto *temp = new Entities::Characters::Zezinho(i, this->get_render(), 46, 62, 0, 0,
                                                       1, sf::Vector2u (8,2), 0.1, Entities::Characters::idle,
                                                       ZE_PATH, &Managers::GraphicManager::delta_time, player);
        this->listaZe.push(temp);
        this->enemies.push_back(temp);
        ListaEnti.LEs.push(temp);
    }

    this->rammus_number = generate_random(3, 7);
    for (int i = 0; i < this->rammus_number; i++) {
        auto *temp = new Entities::Characters::Rammus(i, this->get_render(), 51, 68, 0, 0,
                                                      1, sf::Vector2u (2,2), 0.05, Entities::Characters::idle,
                                                      RAMMUS_PATH, &Managers::GraphicManager::delta_time);
        this->listaRammus.push(temp);
        this->enemies.push_back(temp);
        ListaEnti.LEs.push(temp);
        this->listaFB.push(temp->getFireB());
        ListaEnti.LEs.push(temp->getFireB());
    }
}

void Level2::generate_sizes() {

    for (int i = 0; i < this->platforms.getLen(); i++) {
        auto plat = this->platforms.getItem(i);
        plat->set_size(generate_random(512, 720), generate_random(96, 128));
    }

    for (int i = 0; i < this->walls.getLen(); i++) {
        auto wall = this->walls.getItem(i);
        wall->set_size(32, generate_random(412, 448));
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
        int distrSpaceW = generate_random((plat->get_size().x - 96), (plat->get_size().x - 32)); // the local of wall
        float space = (distrSpaceW + plat->get_position().x);
        wall->set_position(space, 0.0f);
    }

    // generate a position to spikes
    for (int s = 0; s < this->spikes.getLen(); s++) {
        auto spike = this->spikes.getItem(s);
        auto plat = this->platforms.getItem(s);
        int distrSpaceS = generate_random(64, 128);
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
            coin->set_position(aux_c.get_position().x + generate_random(256, 512), this->height - plat->get_size().y - (generate_random(160, 192)));
            aux_c = *coin;
            c_++;
        }
    }

    //generate a position to zes
    for (int s = 0, p = 1; s < this->zezinho_number; s++, p+=2) {
        int distrSpaceS = generate_random(312, 400);
        auto plat = this->platforms.getItem(p);
        float space = (distrSpaceS + plat->get_position().x);
        this->listaZe.getItem(s)->set_position(space, 800);
    }

    //generate a position to rammus
    for (int s = 0, p = 3; s < this->rammus_number; s++, p+=2) {
        int distrSpaceS = generate_random(312, 400);
        auto plat = this->platforms.getItem(p);
        float space = (distrSpaceS + plat->get_position().x);
        this->listaRammus.getItem(s)->set_position(space, 700);
    }
}