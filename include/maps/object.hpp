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
            sf::RectangleShape get_sprite();
            int get_id() const;
            std::string get_name();
            std::string get_type();
            double get_height() const;
            double get_width() const;
            double get_x() const;
            double get_y() const;
            bool get_visible() const;
            void set_position(double x, double y);
            void set_size(double width, double height);
            void set_origin(double x, double y);
            void set_color(sf::Color color);
            void set_thickness(float thick);
            void set_outline_color(sf::Color color);
    };
}


#endif /* end of include guard: OBJECT_HPP_FY69ETVY */
