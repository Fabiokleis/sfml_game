#ifndef OBJECT_HPP_FY69ETVY
#define OBJECT_HPP_FY69ETVY
#include "../rapidjson/document.h" // rapidjson document
#include <iostream>
#include <string>
#include <vector>
#include "collider.hpp"
#include <SFML/Graphics.hpp>

namespace Maps {

    class Object {
        protected:
            std::string name;
            std::string type;
            bool visible;
            int id;
            double height;
            double width;
            double x;
            double y;
            sf::RectangleShape shape;

        public:
            Object();
            Object(rapidjson::Value& value);
            ~Object();

            Controllers::Collider get_collider();
            int get_id() const;
            std::string get_name();
            std::string get_type();
            double get_height() const;
            double get_width() const;
            double get_x() const;
            double get_y() const;
            bool get_visible() const;
    };
}


#endif /* end of include guard: OBJECT_HPP_FY69ETVY */
