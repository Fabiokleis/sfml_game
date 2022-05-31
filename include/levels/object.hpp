#ifndef OBJECT_HPP_FY69ETVY
#define OBJECT_HPP_FY69ETVY
#include "../rapidjson/document.h" // rapidjson document
#include <iostream>
#include <string>
#include "collider.hpp"
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "graphic_manager.hpp"

namespace Levels {

    class Object : public Entities::Entity {

        protected:
            std::string name;
            std::string type;
            int id;
            double height;
            double width;
            double x;
            double y;

        public:
            Object(Managers::GraphicManager &graphic_manager, rapidjson::Value& value);
            ~Object();

            int get_id() const;
            std::string get_name();
            std::string get_type();
            double get_height() const;
            double get_width() const;
            double get_x() const;
            double get_y() const;
            void render();
            virtual void update() = 0;
    };
}


#endif /* end of include guard: OBJECT_HPP_FY69ETVY */
