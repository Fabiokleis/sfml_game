#ifndef LEVEL1_HPP_CAQV1QSO
#define LEVEL1_HPP_CAQV1QSO
#include "level.hpp"

namespace Levels {

    class Level1 : public Level {

        private:
            sf::Texture *coin_tex;
            sf::Texture *spike_tex;



        public:
            Level1();
            Level1(Managers::GraphicManager *graphic_manager, const std::string& map_name, float* pDeltaT);
            ~Level1();

            void build_level();
            void init_textures();
            void generate_instances();
            void generate_sizes();
            void arbritary_positions();
            void update();
    };
}


#endif /* end of include guard: LEVEL1_HPP_CAQV1QSO */
