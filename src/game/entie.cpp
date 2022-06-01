#include "entie.hpp"
using namespace Entities;

Entie::Entie(Managers::GraphicManager *graphicManager) : graphic_manager(graphicManager) {}

Entie::Entie() : graphic_manager() {}

Entie::~Entie() {}

Managers::GraphicManager* Entie::get_render() {
    return this->graphic_manager;
}
