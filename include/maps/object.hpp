#ifndef OBJECT_HPP_FY69ETVY
#define OBJECT_HPP_FY69ETVY
#include "../rapidjson/document.h" // rapidjson document
#include <iostream>
#include <string>

namespace Maps {

    class Object {
        private:
            std::string name;
            std::string type;
            bool visible;
            int id;
            int height;
            int width;
            int x;
            int y;


        public:
            Object();
            Object(rapidjson::Value& value);
            ~Object();

            int get_id();
            std::string get_name();
            std::string get_type();
            int get_height();
            int get_width();
            int get_x();
            int get_y();
            bool get_visible();
    };
}


#endif /* end of include guard: OBJECT_HPP_FY69ETVY */
