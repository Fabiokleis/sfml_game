#include "layer.hpp"

Layer::Layer(rapidjson::Value& value) {
	if (value.HasMember("data")) {
		for (auto& a : value["data"].GetArray()) {
			this->data.push_back(a.GetInt());
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

Layer::~Layer() {}

std::vector<int> Layer::get_data() {
	return this->data;
}

bool Layer::is_visible() {
	return this->visible;
}

int Layer::get_height() {
	return this->height;
}

int Layer::get_id() {
	return this->id;
}

int Layer::get_opacity() {
	return this->opacity;
}

int Layer::get_width() {
	return this->width;
}

int Layer::get_x() {
	return this->x;
}

int Layer::get_y() {
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

