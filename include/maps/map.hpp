#ifndef MAP_HPP_RTB6ZINA
#define MAP_HPP_RTB6ZINA
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/istreamwrapper.h"
#include "../rapidjson/document.h"
#include "layer.hpp"
#include "object.hpp"
#include "platforms.hpp"
#include "locations.hpp"
#include "tiles.hpp"
#include "walls.hpp"
#include "tilemap.hpp"
#include "tilesetmap.hpp"
#include "tileset.hpp"
#include "config.h"
#include "image.hpp"

namespace Maps {

    class Map {
    
        private:
            std::string map_str;
            std::string tileset_buffer;
            int height;
            int width;
            std::vector<Layer> layers;
            std::vector<TileSet> tilesets;
            std::vector<TileSetMap> tileset_maps;
            int tile_height;
            int tile_width;
            std::vector<TileMap> tilemap_render;
            std::vector<Entities::Image> backgrounds;
            Locations locations;
            Tiles tiles;
            Platforms platforms;
            Walls walls;
    
        public:
            Map(std::string map_name);
            ~Map();
    
            void init_variables();
            int get_height() const;
            int get_width() const;
            int get_tile_width() const;
            int get_tile_height() const;

            Locations get_locations();
            Platforms get_platforms();
            Walls get_walls();
            Tiles get_tiles();


            std::vector<TileMap> get_tilemap();
            std::vector<Entities::Image> get_backgrounds();
            void find_tileset(Layer& layer, std::vector<TileSet>& tilesets);
            void load_tileset_buffer(const std::string& filename);
            static std::string read_file(const std::string& filename);
            void load_map(std::string map_name);
            void load_tilesets();
            void load_tilemap();
            void update();
    };
}
#endif /* end of include guard: MAP_HPP_RTB6ZINA */
