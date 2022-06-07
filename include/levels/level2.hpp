#ifndef LEVEL2_HPP_VDZ2MJQB
#define LEVEL2_HPP_VDZ2MJQB
#include "level.hpp"

namespace Levels {

    class Level2 : public Level {

        private:
            sf::Texture *coin_tex;
            sf::Texture *spike_tex;

        public:
            Level2();
            Level2(Managers::GraphicManager *graphic_manager, const std::string& map_name, float* pDeltaT);
            ~Level2();

            void build_level();
            void init_textures();
            void generate_instances();
            void generate_sizes();
            void arbritary_positions();
            void update();
    };
}


#endif /* end of include guard: LEVEL2_HPP_VDZ2MJQB */
