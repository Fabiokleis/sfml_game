#ifndef TILESET_HPP_HYUFE8N1
#define TILESET_HPP_HYUFE8N1
#include <SFML/Graphics.hpp>
#include "../rapidjson/document.h"
#include "../rapidjson/rapidjson.h"
#include "config.h"

namespace Levels {

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
            TileSet(int firstg_id, const std::string& tileset);
            ~TileSet();
    
            int get_firstg_id() const;
        	int get_columns() const;
        	std::string get_image();
        	std::string get_name();
        	int get_tile_height() const;
        	int get_tile_width() const;
    };
}
#endif /* end of include guard: TILESET_HPP_HYUFE8N1 */
