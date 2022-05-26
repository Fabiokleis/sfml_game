#include "locations.hpp"
using namespace Maps;

Locations::Locations(rapidjson::Value &value) {
    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            this->locations_array.emplace_back(obj);
        }
    }
    this->start = this->locations_array[0];
    this->end = this->locations_array[1];
    this->check_point = this->locations_array[2];
}

Locations::Locations() :  locations_array(), start(), check_point(), end() {}

Locations::~Locations() {}

Object Locations::get_start() {
    return this->start;
}

Object Locations::get_check_point() {
    return this->check_point;
}

Object Locations::get_end() {
    return this->end;
}
