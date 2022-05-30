#include "tilesetmap.hpp"
using namespace Maps;


TileSetMap::TileSetMap() : firstid() {}
TileSetMap::~TileSetMap() {}


TileSetMap::TileSetMap(rapidjson::Value& value) {
    this->firstid = value["firstgid"].GetInt();
    this->source = value["source"].GetString();
}

int TileSetMap::get_firstg_id() const {
    return this->firstid;
}

std::string TileSetMap::get_source() {
    return this->source;
}
