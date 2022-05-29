#ifndef LAYER_HPP_HWVVW7IM
#define LAYER_HPP_HWVVW7IM
#include <vector>
#include "tiles.hpp"
#include "platforms.hpp"
#include "walls.hpp"
#include "locations.hpp"
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
            Locations locations;
            Tiles tiles;
            Platforms platforms;
            Walls walls;
    
        public:
            Layer (rapidjson::Value& value);
            Layer();
            ~Layer();

            void init_object_layers(rapidjson::Value& value);
            Locations get_locations();
            Tiles get_tiles();
            Platforms get_platforms();
            Walls get_walls();
            std::vector<long> get_data();
            int get_height() const;
            std::string get_image();
            std::string get_name();
            std::string get_type();
            int get_width() const;
    };
}
#endif /* end of include guard: LAYER_HPP_HWVVW7IM */
