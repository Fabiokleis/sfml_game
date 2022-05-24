#ifndef LAYER_HPP_HWVVW7IM
#define LAYER_HPP_HWVVW7IM
#include <vector>
#include "object.hpp"
#include "../rapidjson/document.h" // rapidjson document

namespace Maps {

    class Layer {
        private:
            std::vector<int> data;
            std::vector<Object> objects;
            int height;
            int id;
            std::string image;
            std::string name;
            int opacity;
            std::string type;
            bool visible;
            int width;
            int x;
            int y;
    
        public:
            Layer();
            Layer (rapidjson::Value& value);
            ~Layer();
            std::vector<int> get_data();
            std::vector<Object> get_objects();
            int get_height() const;
            int get_id() const;
            std::string get_image();
            std::string get_name();
            int get_opacity() const;
            std::string get_type();
            bool is_visible() const;
            int get_width() const;
            int get_x() const;
            int get_y() const;
    };
}
#endif /* end of include guard: LAYER_HPP_HWVVW7IM */
