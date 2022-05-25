#include "locations.hpp"
using namespace Maps;

Locations::Locations(std::vector<Object> locations_array) : locations_array(locations_array) {
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
