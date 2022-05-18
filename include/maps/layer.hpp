#ifndef LAYER_HPP_HWVVW7IM
#define LAYER_HPP_HWVVW7IM
#include <vector>
#include "../rapidjson/document.h" // rapidjson document

namespace Maps {

    class Layer {
        private:
            std::vector<int> data;
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
            int get_height();
            int get_id();
            std::string get_image();
            std::string get_name();
            int get_opacity();
            std::string get_type();
            bool is_visible();
            int get_width();
            int get_x();
            int get_y();
    };
}
#endif /* end of include guard: LAYER_HPP_HWVVW7IM */
