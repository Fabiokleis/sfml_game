#include "object.hpp"
using namespace Maps;

Object::Object(rapidjson::Value& value) {
    this->id = value["id"].GetInt();
    this->name = value["name"].GetString();
    this->type = value["type"].GetString();
    this->height = value["height"].GetDouble();
    this->width = value["width"].GetDouble();
    this->x = value["x"].GetDouble();
    this->y = value["y"].GetDouble();
    this->visible = value["visible"].GetBool();
}

Object::Object() : id(), name(), type(), height(), width(), x(), y(), visible(), Entities::Entity() {}

Object::~Object() {}

sf::RectangleShape Object::get_rect_sprite() {
    return this->sprite;
}

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

bool Object::get_visible() const {
    return this->visible;
}

void Object::set_position(double x, double y) {
    this->sprite.setPosition(x, y);
}
void Object::set_size(double width, double height) {
    this->sprite.setSize(sf::Vector2f(width, height));
}

void Object::set_origin(double x, double y) {
    this->sprite.setOrigin(x, y);
}
void Object::set_color(sf::Color color) {
    this->sprite.setFillColor(color);
}

void Object::set_thickness(float thick) {
    this->sprite.setOutlineThickness(thick);
}
void Object::set_outline_color(sf::Color color) {
    this->sprite.setOutlineColor(color);
}
