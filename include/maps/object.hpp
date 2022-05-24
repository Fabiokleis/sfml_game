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
            bool visible{};
            int id{};
            int height{};
            int width{};
            double x{};
            double y{};

        public:
            Object();
            Object(rapidjson::Value& value);
            ~Object();

            int get_id() const;
            std::string get_name();
            std::string get_type();
            int get_height() const;
            int get_width() const;
            double get_x() const;
            double get_y() const;
            bool get_visible() const;
    };
}


#endif /* end of include guard: OBJECT_HPP_FY69ETVY */
