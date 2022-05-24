#include "object.hpp"
using namespace Maps;

Object::Object(rapidjson::Value& value) {
    this->id = value["id"].GetInt();
    this->name = value["name"].GetString();
    this->type = value["type"].GetString();
    this->height = value["height"].GetInt();
    this->width = value["width"].GetInt();
    this->x = value["x"].GetDouble();
    this->y = value["y"].GetDouble();
    this->visible = value["visible"].GetBool();
}
Object::Object() = default;

Object::~Object() = default;;

int Object::get_id() const {
    return this->id;
}

std::string Object::get_name() {
    return this->name;
}

std::string Object::get_type() {
    return this->type;
}

int Object::get_height() const {
    return this->height;
}

int Object::get_width() const {
    return this->width;
}

double Object::get_x() const {
    return this->x;
}

double Object::get_y() const {
    return this->y;
}

bool Object::get_visible() const {
    return this->visible;
}
