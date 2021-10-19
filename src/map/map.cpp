#include <iostream>
#include <fstream>
#include "map.hpp"
#include "layer.hpp"
#include "tilesetmap.hpp"
#include "config.h"

Map::Map() {
    this->load_map();
    this->init_variables();
    this->load_tilesets();
    this->load_tilemap();
}

Map::~Map() {
    delete map_str;
    delete tileset_buffer;
}

void Map::init_variables() {

    rapidjson::Document map_doc;

    map_doc.Parse(this->map_str);

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

int Map::get_height() {
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

std::vector<TileSet> Map::get_tilesets() {
    return this->tilesets;
}

std::vector<Layer> Map::get_layers() {
    return this->layers;
}

/* TEG */

// set buffer to each space
void Map::load_map() {
    std::string path = RESOURCE_PATH;
    path += "map/platform.json";

    this->map_str = this->read_file(path);
}

void Map::load_tileset_buffer(std::string filename) {
    std::string path = RESOURCE_PATH;
    path += "map/" + filename;

    this->tileset_buffer = this->read_file(path);
}

// read a buffer of json file and returns
inline const char* Map::read_file(std::string filename) {

    std::cout << filename << "\n";
    FILE* f = fopen(filename.c_str(), "r");

	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);

	char* buffer = new char[size];

	rewind(f);
	fread(buffer, sizeof(char), size, f);

    std::cout << buffer;
	return buffer;
}

// get by firstg_id if a tile is set or not
TileSet Map::find_tileset(Layer& layer, std::vector<TileSet>& tilesets) {
    for (auto data : layer.get_data()) {
        if (data != 0) {
            for (auto& tile : tilesets) {
                std::cout << data << "\n";
                std::cout << tile.get_firstg_id() << "\n";

                if (tile.get_firstg_id() == data) {
                    return tile;
                }
            }
        }
    }
}

// initialize each tile of map puttin into vactor of tiles
void Map::load_tilesets() {
    for (size_t i = 0; i < this->tileset_maps.size(); i++) {
        std::string file = this->tileset_maps[i].get_source();
        this->load_tileset_buffer(file);

        TileSet tileset(this->tileset_maps[i].get_firstg_id(), this->tileset_buffer);

        this->tilesets.push_back(tileset);
    }
}

// pass all informations parsed to be a new tilemap
void Map::load_tilemap() {
    for (size_t i = 0; i < this->layers.size(); i++) {
        if (this->layers[i].get_type() == "tilelayer") {
            this->tilemap_render.push_back(TileMap());
            this->tilemap_render.back()
            .load(this->find_tileset(this->layers[i], this->tilesets),this->layers[i]);
        }
    }
}

void Map::update() {}

void Map::render(sf::RenderTarget* target) {
    for (int i = this->tilemap_render.size() - 1; i >= 0; i--) {
        target->draw(this->tilemap_render[i]);
    }
}