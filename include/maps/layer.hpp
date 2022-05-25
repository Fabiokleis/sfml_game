#ifndef LAYER_HPP_HWVVW7IM
#define LAYER_HPP_HWVVW7IM
#include <vector>
#include "object.hpp"
#include "../rapidjson/document.h" // rapidjson document

namespace Maps {

    class Layer {
        private:
            std::vector<long> data;
            int height;
            int width;
            std::string image;
            std::string name;
            std::string type;
            std::vector<Object> objs;
    
        public:
            Layer (rapidjson::Value& value);
            Layer();
            ~Layer();
            std::vector<long> get_data();
            std::vector<Object> get_objects();
            int get_height() const;
            std::string get_image();
            std::string get_name();
            std::string get_type();
            int get_width() const;
    };
}
#endif /* end of include guard: LAYER_HPP_HWVVW7IM */
