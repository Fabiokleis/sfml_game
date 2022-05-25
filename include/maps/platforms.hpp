#ifndef PLATFORMS_HPP_KWHTQICM
#define PLATFORMS_HPP_KWHTQICM
#include "object.hpp"
#include <iostream>
#include <vector>

namespace Maps {

    class Platforms : public Object {
        
        private:
            std::vector<Object> platforms_array;

        public:
            Platforms();
            Platforms(std::vector<Object> platforms_array);
            std::vector<Object> get_platforms();
            ~Platforms();
    };
}


#endif /* end of include guard: PLATFORMS_HPP_KWHTQICM */
