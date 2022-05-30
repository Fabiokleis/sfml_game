#include "object.hpp"
using namespace Maps;

Object::Object(rapidjson::Value& value) : Entities::Entity() {
    this->id = value["id"].GetInt();
    this->name = value["name"].GetString();
    this->type = value["type"].GetString();
    this->height = value["height"].GetDouble();
    this->width = value["width"].GetDouble();
    this->x = value["x"].GetDouble();
    this->y = value["y"].GetDouble();
}

Object::Object() : id(), name(), type(), height(), width(), x(), y(), Entities::Entity() {}

Object::~Object() {}

Controllers::Collider Object::get_collider() {
    return Controllers::Collider{this->sprite};
}

int Object::get_id() const {
    return this->id;
}

std::string Object::get_name() {
    return this->name;
}

std::string Object::get_type() {
    return this->type;
}

double Object::get_height() const {
    return this->height;
}

double Object::get_width() const {
    return this->width;
}

double Object::get_x() const {
    return this->x;
}

double Object::get_y() const {
    return this->y;
}
