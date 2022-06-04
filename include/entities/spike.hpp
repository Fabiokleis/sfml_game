#ifndef SPIKE_HPP_JIX7N9ST
#define SPIKE_HPP_JIX7N9ST
#include "obstacle.hpp"

namespace Entities {

class Spike : public Obstacle {
    private:

    public:
        Spike();
        Spike(Managers::GraphicManager *graphic_manager, double x, double y, double width, double height,  const std::string &path_name);

        void update();
        ~Spike();
    };
}


#endif /* end of include guard: SPIKE_HPP_JIX7N9ST */
