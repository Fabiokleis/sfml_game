#ifndef GAME_LISTAENTITIES_H
#define GAME_LISTAENTITIES_H
#include "Lista.h"
#include "entity.hpp"

namespace Listas {
    class ListaEntidades
    {
    private:
    public:
        Lista<Entities::Entity> LEs;

        ListaEntidades(){}
        ~ListaEntidades(){}
    };
}


#endif //GAME_LISTAENTITIES_H
