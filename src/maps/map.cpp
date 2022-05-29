#include <iostream>
#include <fstream>
#include "map.hpp"
#include "layer.hpp"
#include "tilesetmap.hpp"
#include "config.h"
using namespace Maps;

Map::Map(std::string map_name) :
    height(), width(), tile_height(), tile_width(), locations(), platforms(), walls(), tiles()
{
    this->load_map(map_name);
    this->init_variables();
    this->load_tilesets();
    this->load_tilemap();
}

Map::~Map() = default;

void Map::init_variables() {

    rapidjson::Document map_doc;

    map_doc.Parse(this->map_str.c_str());


    if (map_doc.HasMember("properties")) {
        rapidjson::Value::Array  prop_arr = map_doc["properties"].GetArray();
        for (auto &prop : prop_arr) {
            if (prop.HasMember("value")) {
                this->map_name = prop["value"].GetString();
            }
        }
    }

    this->height = map_doc["height"].GetInt();

    rapidjson::Value::Array layer_a = map_doc["layers"].GetArray();

    for (auto& layer : layer_a) {
        layers.emplace_back(layer);
    }

    std::reverse(layers.begin(), layers.end());

    for (auto &layer : layers) {
        // pass all informations parsed to be a new location obj
        if (layer.get_name() == "locations") {
            this->locations = layer.get_locations();
        }
        // pass all informations parsed to be a new platform obj
        if (layer.get_name() == "platforms") {
            this->platforms = layer.get_platforms();
        }
        // pass all informations parsed to be a new tile obj
        if (layer.get_name() == "tiles") {
            this->tiles = layer.get_tiles();
        }
        // pass all informations parsed to be a new wall obj
        if (layer.get_name() == "walls") {
            this->walls = layer.get_walls();
        }
    }

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

std::string Map::get_name() {
    return this->map_name;
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
void Map::load_map(std::string map_name) {
    std::string path = RESOURCE_PATH;
    path += "map/" + map_name;
    this->map_str = Maps::Map::read_file(path);
}

void Map::load_tileset_buffer(const std::string& filename) {
    std::string path = RESOURCE_PATH;
    path += "map/" + filename;
    this->tileset_buffer = Maps::Map::read_file(path);
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

// read a file and returns
std::string Map::read_file(const std::string& filename) {
    std::cout << filename << "\n";
    std::ostringstream buf;
    std::ifstream input(filename.c_str());
    buf << input.rdbuf();
    std::cout << buf.str();
    return buf.str();
}