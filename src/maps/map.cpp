#include <iostream>
#include <fstream>
#include "map.hpp"
#include "layer.hpp"
#include "tilesetmap.hpp"
#include "config.h"
using namespace Maps;

Map::Map() {
    this->load_map();
    this->init_variables();
    this->load_tilesets();
    this->load_tilemap();
    this->init_tiles();
}

Map::~Map() = default;

void Map::init_variables() {

    rapidjson::Document map_doc;

    map_doc.Parse(this->map_str.c_str());

    this->height = map_doc["height"].GetInt();
    this->infinite = map_doc["infinite"].GetBool();

    rapidjson::Value::Array layer_a = map_doc["layers"].GetArray();

    for (size_t i = 0; i < layer_a.Capacity(); i++) {
        Layer layer(layer_a[i]);
        layers.push_back(layer);
    }

    std::reverse(layers.begin(), layers.end());

    this->next_layer_id = map_doc["nextlayerid"].GetInt();
    this->next_object_id = map_doc["nextobjectid"].GetInt();
    this->orientation = map_doc["orientation"].GetString();
    this->render_order = map_doc["renderorder"].GetString();
    this->tile_height = map_doc["tileheight"].GetInt();

    rapidjson::Value::Array tile_set_array = map_doc["tilesets"].GetArray();

    for (size_t i = 0; i < tile_set_array.Capacity(); i++) {
        TileSetMap tileset(tile_set_array[i]);
        this->tileset_maps.push_back(tileset);
    }

    std::reverse(this->tileset_maps.begin(), tileset_maps.end());

    this->tile_width = map_doc["tilewidth"].GetInt();
    this->width = map_doc["width"].GetInt();
}

/* GET */

int Map::get_height() const {
    return this->height;
}

int Map::get_width() {
    return this->width;
}

int Map::get_next_layer_id() {
    return this->next_layer_id;
}

int Map::get_next_object_id() {
    return this->next_object_id;
}

int Map::get_tile_width() {
    return this->tile_width;
}

int Map::get_tile_height() {
    return this->tile_height;
}

bool Map::is_infinite() {
    return this->infinite;
}

std::string Map::get_orientation() {
    return this->orientation;
}

std::string Map::get_render_order() {
    return this->render_order;
}

std::vector<TileSetMap> Map::get_tile_set_map() {
    return this->tileset_maps;
}

std::vector<TileSet>& Map::get_tilesets() {
    return this->tilesets;
}

std::vector<TileMap> Map::get_tilemap() {
    return this->tilemap_render;
}

std::vector<Layer> Map::get_layers() {
    return this->layers;
}
std::vector<Tile> Map::get_tiles() {
    return this->tiles;
}

std::vector<Entities::Image> Map::get_backgrounds() {
    return this->backgrounds;
}


/* TEG */

// set buffer to each space
void Map::load_map() {
    std::string path = RESOURCE_PATH;
    path += "map/platform.json";
    this->map_str = this->read_file(path);
}

void Map::load_tileset_buffer(const std::string& filename) {
    std::string path = RESOURCE_PATH;
    path += "map/" + filename;
    this->tileset_buffer = this->read_file(path);
}

// read a buffer of json file and returns
std::string Map::read_file(const std::string& filename) {
    std::cout << filename << "\n";
    std::ostringstream buf; 
    std::ifstream input(filename.c_str()); 
    buf << input.rdbuf(); 
    std::cout << buf.str();
    return buf.str();
}

// initialize each tile of map putting into vector of tiles
void Map::load_tilesets() {
    for (auto & tileset_map : this->tileset_maps) {
        std::string file = tileset_map.get_source();
        this->load_tileset_buffer(file);

        TileSet tileset(tileset_map.get_firstg_id(), this->tileset_buffer);

        this->tilesets.push_back(tileset);
    }
}

// pass all informations parsed to be a new tilemap
void Map::load_tilemap() {
    for (auto & layer : this->layers) {
        if (layer.get_type() == "tilelayer") {
            this->tilemap_render.emplace_back();
            this->find_tileset(layer, this->tilesets);
        }
        if (layer.get_type() == "imagelayer") {
            this->backgrounds.emplace_back("map/"+layer.get_image());
        }
    }
}

// get by firstg_id if a tile is set or not
void Map::find_tileset(Layer& layer, std::vector<TileSet>& tilesets) {
    for (auto& tile: tilesets) {
        this->tilemap_render.back().load(tile, layer);
    }
}

void Map::init_tiles() {
    this->tiles = this->tilemap_render.back().get_tiles();
}

void Map::update() {}