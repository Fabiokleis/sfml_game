#ifndef LEVEL2_HPP_VDZ2MJQB
#define LEVEL2_HPP_VDZ2MJQB
#include "level.hpp"

namespace Levels {

    class Level2 : public Level {

        private:


        public:
            Level2();
            Level2(Managers::GraphicManager *graphic_manager, const std::string& map_name);
            ~Level2();

            void build_level();
            void update();
            void render();
    };
}


#endif /* end of include guard: LEVEL2_HPP_VDZ2MJQB */
