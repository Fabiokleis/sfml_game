#include "layer.hpp"
using namespace Maps;

Layer::Layer(rapidjson::Value& value) {
	if (value.HasMember("data")) {
		for (auto& i : value["data"].GetArray()) {
			this->data.push_back(i.GetInt());
		}
	}

    if (value.HasMember("objects")) {
        for (auto& obj : value["objects"].GetArray()) {
            this->objects.emplace_back(obj);
        }
    }

	if (value.HasMember("height")) {
		this->height = value["height"].GetInt();
	}

	this->id = value["id"].GetInt();

	if (value.HasMember("image")) {
		this->image = value["image"].GetString();
	}

	this->name = value["name"].GetString();
	this->opacity = value["opacity"].GetInt();
	this->type = value["type"].GetString();
	this->visible = value["visible"].GetBool();
	
	if (value.HasMember("width")) {
		this->width = value["width"].GetInt();
	}

 	this->x = value["x"].GetInt();
	this->y = value["y"].GetInt();
}

Layer::~Layer() = default;

std::vector<int> Layer::get_data() {
	return this->data;
}

std::vector<Maps::Object> Layer::get_objects() {
    return this->objects;
}

bool Layer::is_visible() const {
	return this->visible;
}

int Layer::get_height() const {
	return this->height;
}

int Layer::get_id() const {
	return this->id;
}

int Layer::get_opacity() const {
	return this->opacity;
}

int Layer::get_width() const {
	return this->width;
}

int Layer::get_x() const {
	return this->x;
}

int Layer::get_y() const {
	return this->y;
}

std::string Layer::get_image() {
	return this->image;
}

std::string Layer::get_name() {
	return this->name;
}

std::string Layer::get_type() {
	return this->type;
}

