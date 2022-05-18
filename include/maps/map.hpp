#ifndef MAP_HPP_RTB6ZINA
#define MAP_HPP_RTB6ZINA
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/istreamwrapper.h"
#include "../rapidjson/document.h"
#include "layer.hpp"
#include "tilemap.hpp"
#include "tilesetmap.hpp"
#include "tileset.hpp"
#include "config.h"
#include "tile.hpp"

namespace Maps {

    class Map {
    
        private:
            std::string map_str;
            std::string tileset_buffer;
            int height;
            int width;
            bool infinite;
            std::vector<Layer> layers;
            int next_layer_id;
            int next_object_id;
            std::string orientation;
            std::string render_order;
            std::vector<TileSet> tilesets;
            std::vector<TileSetMap> tileset_maps;
            int tile_height;
            int tile_width;
            std::vector<TileMap> tilemap_render;
            std::vector<Tile> tiles;
    
        public:
            Map();
            ~Map();
    
            void init_variables();
            int get_height();
            int get_width();
            int get_next_layer_id();
            int get_next_object_id();
            int get_tile_width();
            int get_tile_height();
            std::vector<Tile> get_tiles();
            bool is_infinite();
    
            std::string get_orientation();
            std::string get_render_order();
            std::vector<TileSet> & get_tilesets();
            std::vector<TileSetMap> get_tile_set_map();
            std::vector<Layer> get_layers();
            void find_tileset(Layer& layer, std::vector<TileSet>& tilesets);
            void load_tileset_buffer(std::string filename);
            std::string read_file(std::string filename);
            void load_map();
            void load_tilesets();
            void load_tilemap();
            void init_tiles();
            void update();
            void render(sf::RenderTarget* target);
    };
}
#endif /* end of include guard: MAP_HPP_RTB6ZINA */