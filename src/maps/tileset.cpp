#include <iostream>
#include "tileset.hpp"
using namespace Maps;

TileSet::TileSet (int firstg_id, const std::string& tileset) {
    this->firstg_id = firstg_id;
    rapidjson::Document tileset_doc;
    tileset_doc.Parse(tileset.c_str());

    this->columns = tileset_doc["columns"].GetInt();
    this->image = tileset_doc["image"].GetString();
    this->image_height = tileset_doc["imageheight"].GetInt();
    this->image_width = tileset_doc["imagewidth"].GetInt();
    this->margin = tileset_doc["margin"].GetInt();
    this->name = tileset_doc["name"].GetString();
    this->spacing = tileset_doc["spacing"].GetInt();
    this->tile_count = tileset_doc["tilecount"].GetInt();
    this->tile_height = tileset_doc["tileheight"].GetInt();
    this->tile_width = tileset_doc["tilewidth"].GetInt();
    this->type = tileset_doc["type"].GetString();
}

TileSet::TileSet() : firstg_id(), columns(), image(), image_height(), image_width(),
        margin(), name(), tile_width(), tile_height(), type(), tile_count(), spacing() {}

TileSet::~TileSet() {}

int TileSet::get_firstg_id() const {
    return this->firstg_id;
}

int TileSet::get_columns() const {
    return this->columns;
}

int TileSet::get_image_height() const {
    return this->image_height;
}

int TileSet::get_image_width() const {
    return this->image_width;
}

int TileSet::get_margin() const {
    return this->margin;
}

int TileSet::get_spacing() const {
    return this->spacing;
}

int TileSet::get_tile_count() const {
    return this->tile_count;
}

int TileSet::get_tile_height() const {
    return this->tile_height;
}

int TileSet::get_tile_width() const {
    return this->tile_width;
}

std::string TileSet::get_name() {
    return this->name;
}

std::string TileSet::get_image() {
    return this->image;
}
std::string TileSet::get_type() {
    return this->type;
}
