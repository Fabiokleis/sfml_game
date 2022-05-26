#ifndef TILES_HPP_30AHWVXM
#define TILES_HPP_30AHWVXM
#include "object.hpp"
#include <iostream>
#include <vector>

namespace Maps {

    class Tiles : public Object {
        private:
            std::vector<Object> tiles_array;
            std::vector<Object> tiles_rect_array;
            std::vector<Object> tiles_triangle_array;

        public:
            Tiles();
            Tiles(rapidjson::Value& value);
            std::vector<Object> get_tiles();
            ~Tiles();
    };
}
#endif /* end of include guard: TILES_HPP_30AHWVXM */
