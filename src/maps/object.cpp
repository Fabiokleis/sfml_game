#include "object.hpp"
using namespace Maps;

Object::Object(rapidjson::Value& value) {
    this->id = value["id"].GetInt();
    this->name = value["name"].GetString();
    this->type = value["type"].GetString();
    this->height = value["height"].GetInt();
    this->width = value["width"].GetInt();
    this->x = value["x"].GetInt();
    this->y = value["y"].GetInt();
    this->visible = value["visible"].GetBool();
}

Object::~Object() {};

int Object::get_id() {
    return this->id;
}

std::string Object::get_name() {
    return this->name;
}

std::string Object::get_type() {
    return this->type;
}

int Object::get_height() {
    return this->height;
}

int Object::get_width() {
    return this->width;
}

int Object::get_x() {
    return this->x;
}

int Object::get_y() {
    return this->y;
}

bool Object::get_visible() {
    return this->visible;
}
