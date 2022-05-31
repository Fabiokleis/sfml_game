#ifndef LOCATIONS_HPP_GOBR3XIQ
#define LOCATIONS_HPP_GOBR3XIQ
#include "object.hpp"
#include "../rapidjson/document.h"

namespace Levels {
    
    class Locations : public Object {
            
        private:
            std::vector<Object> locations_array;
            std::vector<Object> check_points;
            Object start;
            Object end;

        public:
            Locations();
            Locations(rapidjson::Value &value);
            ~Locations();
            Object& get_start();
            std::vector<Object> get_check_points();
            Object& get_end();
    };
}


#endif /* end of include guard: LOCATIONS_HPP_GOBR3XIQ */
