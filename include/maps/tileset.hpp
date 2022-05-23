#ifndef TILESET_HPP_HYUFE8N1
#define TILESET_HPP_HYUFE8N1
#include <SFML/Graphics.hpp>
#include "../rapidjson/document.h"
#include "../rapidjson/rapidjson.h"
#include "config.h"

namespace Maps {

    class TileSet {
        private:
    
            int firstg_id;
        	int columns;
        	std::string image;
        	int image_height;
        	int image_width;
        	int margin;
        	std::string name;
            int spacing;
        	int tile_count;
        	int tile_height;
        	int tile_width;
        	std::string type;
    
        public:
            TileSet();
            TileSet(int firstg_id, std::string tileset);
            ~TileSet();
    
            int get_firstg_id();
        	int get_columns();
        	std::string get_image();
        	int get_image_height(); 
        	int get_image_width();
        	int get_margin();
        	std::string get_name();
        	int get_spacing();
        	int get_tile_count();
        	int get_tile_height();
        	int get_tile_width();
        	std::string get_type();
    
    };
}
#endif /* end of include guard: TILESET_HPP_HYUFE8N1 */
