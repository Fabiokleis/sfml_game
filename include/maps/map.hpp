#ifndef MAP_HPP_RTB6ZINA
#define MAP_HPP_RTB6ZINA
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/istreamwrapper.h"
#include "../rapidjson/document.h"
#include "layer.hpp"
#include "object.hpp"
#include "tilemap.hpp"
#include "tilesetmap.hpp"
#include "tileset.hpp"
#include "config.h"
#include "tile.hpp"
#include "image.hpp"

namespace Maps {

    class Map {
    
        private:
            std::string map_str;
            std::string tileset_buffer;
            int height{};
            int width{};
            bool infinite{};
            std::vector<Layer> layers;
            int next_layer_id{};
            int next_object_id{};
            std::string orientation;
            std::string render_order;
            std::vector<TileSet> tilesets;
            std::vector<TileSetMap> tileset_maps;
            int tile_height{};
            int tile_width{};
            std::vector<TileMap> tilemap_render;
            std::vector<Tile> tiles;
            std::vector<Entities::Image> backgrounds;
            std::vector<Object> locations;
    
        public:
            Map();
            ~Map();
    
            void init_variables();
            int get_height() const;
            int get_width() const;
            int get_next_layer_id() const;
            int get_next_object_id() const;
            int get_tile_width() const;
            int get_tile_height() const;
            std::vector<Tile> get_tiles();
            bool is_infinite() const;
    
            std::string get_orientation();
            std::string get_render_order();
            std::vector<TileSet> & get_tilesets();
            std::vector<TileSetMap> get_tile_set_map();
            std::vector<TileMap> get_tilemap();
            std::vector<Entities::Image> get_backgrounds();
            std::vector<Object> get_locations();
            std::vector<Layer> get_layers();
            void find_tileset(Layer& layer, std::vector<TileSet>& tilesets);
            void load_tileset_buffer(const std::string& filename);
            std::string read_file(const std::string& filename);
            void load_map();
            void load_tilesets();
            void load_tilemap();
            void init_tiles();
            void update();
    };
}
#endif /* end of include guard: MAP_HPP_RTB6ZINA */
