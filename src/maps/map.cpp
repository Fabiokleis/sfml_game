#include <iostream>
#include <fstream>
#include "map.hpp"
#include "layer.hpp"
#include "tilesetmap.hpp"
#include "config.h"
using namespace Maps;

Map::Map() :
    height(), width(), tile_height(), tile_width(), locations(), platforms(), walls(), tiles()
{
    this->load_map();
    this->init_variables();
    this->load_tilesets();
    this->load_tilemap();
}

Map::~Map() = default;

void Map::init_variables() {

    rapidjson::Document map_doc;

    map_doc.Parse(this->map_str.c_str());

    this->height = map_doc["height"].GetInt();

    rapidjson::Value::Array layer_a = map_doc["layers"].GetArray();

    for (auto& layer : layer_a) {
        layers.emplace_back(layer);
    }

    std::reverse(layers.begin(), layers.end());

    this->tile_height = map_doc["tileheight"].GetInt();

    rapidjson::Value::Array tile_set_array = map_doc["tilesets"].GetArray();

    for (auto& tileset : tile_set_array) {
        this->tileset_maps.emplace_back(tileset);
    }

    std::reverse(this->tileset_maps.begin(), tileset_maps.end());

    this->tile_width = map_doc["tilewidth"].GetInt();
    this->width = map_doc["width"].GetInt();

}

int Map::get_height() const {
    return this->height;
}

int Map::get_width() const {
    return this->width;
}

int Map::get_tile_width() const {
    return this->tile_width;
}

int Map::get_tile_height() const {
    return this->tile_height;
}

std::vector<TileMap> Map::get_tilemap() {
    return this->tilemap_render;
}

std::vector<Entities::Image> Map::get_backgrounds() {
    return this->backgrounds;
}

Locations Map::get_locations() {
    return this->locations;
}

Platforms Map::get_platforms() {
    return this->platforms;
}

Walls Map::get_walls() {
    return this->walls;
}

Tiles Map::get_tiles() {
    return this->tiles;
}

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


void Map::load_tilemap() {
    for (auto & layer : this->layers) {
        // pass all informations parsed to be a new tilemap
        if (layer.get_type() == "tilelayer") {
            this->tilemap_render.emplace_back();
            this->find_tileset(layer, this->tilesets);
        }
        // pass all informations parsed to be a new location obj
        if (layer.get_name() == "locations") {
            this->locations = Locations(layer.get_objects());
        }
        // pass all informations parsed to be a new platform obj
        if (layer.get_name() == "platforms") {
            this->platforms = Platforms(layer.get_objects());
        }
        // pass all informations parsed to be a new tile obj
        if (layer.get_name() == "tiles") {
            this->tiles = Tiles(layer.get_objects());
        }
        // pass all informations parsed to be a new wall obj
        if (layer.get_name() == "walls") {
            this->walls = Walls(layer.get_objects());
        }
        // pass all informations parsed to be a new image
        if (layer.get_type() == "imagelayer") {
            this->backgrounds.emplace_back("map/"+layer.get_image());
        }
    }
}

void Map::find_tileset(Layer& layer, std::vector<TileSet>& tilesets_) {
    for (auto& tile: tilesets_) {
        this->tilemap_render.back().load(tile, layer);
    }
}

void Map::update() {}