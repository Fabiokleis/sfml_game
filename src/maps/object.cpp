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

    if (value.HasMember("polygon")) {
        for (auto &obj : value["polygon"].GetArray()) {
            this->polys.push_back(obj["x"].GetDouble());
            this->polys.push_back(obj["y"].GetDouble());
        }
        this->triangle.setPointCount(3);
    }
}

Object::Object() : id(), name(), type(), height(), width(), x(), y(), visible(), shape(), triangle() {}

Object::~Object() = default;

std::vector<double> Object::get_polys() {
    return this->polys;
}

sf::RectangleShape Object::get_rect_sprite() {
    return this->shape;
}

Controllers::Collider Object::get_collider() {
    return Controllers::Collider{this->shape};
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
    this->shape.setPosition(x, y);
}
void Object::set_size(double width, double height) {
    this->shape.setSize(sf::Vector2f(width, height));
}

void Object::set_origin(double x, double y) {
    this->shape.setOrigin(x, y);
}
void Object::set_color(sf::Color color) {
    this->shape.setFillColor(color);
}

void Object::set_thickness(float thick) {
    this->shape.setOutlineThickness(thick);
}
void Object::set_outline_color(sf::Color color) {
    this->shape.setOutlineColor(color);
}

sf::ConvexShape Object::get_triangle_sprite() {
    return this->triangle;
}

void Object::set_point(int point, double x_, double y_) {
    this->triangle.setPoint(point, sf::Vector2f(x_, y_));
}
