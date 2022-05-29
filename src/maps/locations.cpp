#include "locations.hpp"
using namespace Maps;

Locations::Locations(rapidjson::Value &value) {
    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            this->locations_array.emplace_back(obj);
        }
    }
    for (auto &obj : this->locations_array) {

        obj.set_position(obj.get_x(), obj.get_y());
        obj.set_size(obj.get_width(), obj.get_height());
        obj.set_origin(obj.get_width() / 2.0f, obj.get_height() / 2.0f);
        if (obj.get_name() == "checkpoint") {
            this->check_points.push_back(obj);
        }
    }
    this->start = this->locations_array[0];
    this->end = this->locations_array[1];

}

Locations::Locations() :  locations_array(), start(), end() {}

Locations::~Locations() {}

Object& Locations::get_start() {
    return this->start;
}

std::vector<Object> Locations::get_check_points() {
    return this->check_points;
}

Object& Locations::get_end() {
    return this->end;
}
