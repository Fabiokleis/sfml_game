#include "tilesetmap.hpp"


TileSetMap::TileSetMap() {}
TileSetMap::~TileSetMap() {}

TileSetMap::TileSetMap(rapidjson::Value& value) {
    this->firstid = value["firstgid"].GetInt();
    this->source = value["source"].GetString();
}

int TileSetMap::get_firstg_id() {
    return this->firstid;
}

std::string TileSetMap::get_source() {
    return this->source;
}