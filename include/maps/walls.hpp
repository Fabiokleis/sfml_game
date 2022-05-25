#ifndef WALLS_HPP_XKLPJ4FY
#define WALLS_HPP_XKLPJ4FY
#include "object.hpp"
#include <iostream>
#include <vector>

namespace Maps {

    class Walls : public Object {
        private:
            std::vector<Object> walls_array;

        public:
            Walls();
            Walls(std::vector<Object> walls_array);
            std::vector<Object> get_walls();
            ~Walls();

    };
}



#endif /* end of include guard: WALLS_HPP_XKLPJ4FY */
