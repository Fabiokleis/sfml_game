#ifndef LEVEL_HPP_RTB6ZINA
#define LEVEL_HPP_RTB6ZINA
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
#include "tilesetwrapper.hpp"
#include "tileset.hpp"
#include "config.h"
#include "image.hpp"
#include "entie.hpp"

namespace Levels {

class Level : public Entities::Entie {
    
        private:
            std::string map_str;
            std::string tileset_buffer;
            int height;
            int width;
            int tile_height;
            int tile_width;

            std::string map_name;
            std::vector<Layer> layers;
            std::vector<TileSet> tilesets;
            std::vector<TileSetWrapper> tileset_wrappers;
            std::vector<TileMap> tilemap_render;

            Entities::Image background;
            Locations locations;
            Tiles tiles;
            Platforms platforms;
            Walls walls;
    
        public:
            Level(std::string map_name);
            ~Level();
    
            void init_variables();
            int get_height() const;
            int get_width() const;
            int get_tile_width() const;
            int get_tile_height() const;

            std::vector<TileMap> get_tilemap();
            std::string get_name();
            static std::string read_file(const std::string& filename);
            void find_tileset(Layer& layer, std::vector<TileSet>& tilesets);
            void load_tileset_buffer(const std::string& filename);
            void load_map(std::string map_name);
            void load_tilesets();
            void load_tilemap();
            void update();
            void render();
    };
}

#endif /* end of include guard: LEVEL_HPP_RTB6ZINA */
