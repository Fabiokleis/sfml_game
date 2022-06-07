#ifndef ENTIE_HPP_NUO0WDEY
#define ENTIE_HPP_NUO0WDEY
#include <iostream>
#include <SFML/Graphics.hpp>
#include "graphic_manager.hpp"


class Entie {
    protected:
        Managers::GraphicManager *graphic_manager;

    public:
        Entie();
        Entie(Managers::GraphicManager *graphicManager);
        ~Entie();

        Managers::GraphicManager* get_render();
        virtual void render() = 0;
        virtual void update() = 0;
};

#endif /* end of include guard: ENTIE_HPP_NUO0WDEY */
