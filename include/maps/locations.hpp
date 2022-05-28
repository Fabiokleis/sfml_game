#ifndef LOCATIONS_HPP_GOBR3XIQ
#define LOCATIONS_HPP_GOBR3XIQ
#include "object.hpp"
#include "../rapidjson/document.h"

namespace Maps {
    
    class Locations : public Object {
            
        private:
            std::vector<Object> locations_array;
            Object start;
            Object check_point;
            Object end;

        public:
            Locations();
            Locations(rapidjson::Value &value);
            ~Locations();
            Object& get_start();
            Object& get_check_point();
            Object& get_end();
    };
}


#endif /* end of include guard: LOCATIONS_HPP_GOBR3XIQ */
