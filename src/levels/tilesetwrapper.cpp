#include "tilesetwrapper.hpp"
using namespace Levels;

TileSetWrapper::TileSetWrapper() : firstid() {}
TileSetWrapper::~TileSetWrapper() {}

TileSetWrapper::TileSetWrapper(rapidjson::Value& value) {
    this->firstid = value["firstgid"].GetInt();
    this->source = value["source"].GetString();
}

int TileSetWrapper::get_firstg_id() const {
    return this->firstid;
}

std::string TileSetWrapper::get_source() {
    return this->source;
}
