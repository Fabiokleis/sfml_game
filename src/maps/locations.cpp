#include "locations.hpp"
using namespace Maps;

Locations::Locations(rapidjson::Value &value) {
    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            this->locations_array.emplace_back(obj);
        }
    }
    this->start = this->locations_array[0];
    this->start.set_position(this->start.get_x(), this->start.get_y());
    this->start.set_size(this->start.get_width(), this->start.get_height());
    this->start.set_origin(this->start.get_width() / 2.0f, this->start.get_height() / 2.0f);
    this->end = this->locations_array[1];
    this->end.set_position(this->end.get_x(), this->end.get_y());
    this->end.set_size(this->end.get_width(), this->end.get_height());
    this->end.set_origin(this->end.get_width() / 2.0f, this->end.get_height() / 2.0f);
    this->check_point = this->locations_array[2];
    this->check_point.set_position(this->check_point.get_x(), this->check_point.get_y());
    this->check_point.set_size(this->check_point.get_width(), this->check_point.get_height());
    this->check_point.set_origin(this->check_point.get_width() / 2.0f, this->check_point.get_height() / 2.0f);

}

Locations::Locations() :  locations_array(), start(), check_point(), end() {}

Locations::~Locations() {}

Object& Locations::get_start() {
    return this->start;
}

Object& Locations::get_check_point() {
    return this->check_point;
}

Object& Locations::get_end() {
    return this->end;
}
