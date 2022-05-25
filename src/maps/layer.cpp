#include "layer.hpp"
using namespace Maps;

Layer::Layer(rapidjson::Value& value) {
    // in case the layer type is tilelayer
	if (value.HasMember("data")) {
		for (auto& i : value["data"].GetArray()) {
			this->data.push_back(i.GetInt64());
		}
	}
    // case a layer of objects
    if (value.HasMember("objects")) {
        for (auto &obj : value["objects"].GetArray()) {
            this->objs.emplace_back(obj);
        }
    }

    // in case the layer type is image
	if (value.HasMember("image")) {
		this->image = value["image"].GetString();
	}

    // default options inside any layer, some are missing
	this->name = value["name"].GetString();
	this->type = value["type"].GetString();

    if (value.HasMember("height")) {
        this->height = value["height"].GetInt();
    }
	if (value.HasMember("width")) {
		this->width = value["width"].GetInt();
	}
}

Layer::Layer() : name(), type(), width(), height(), objs() {}

Layer::~Layer() = default;

std::vector<Object> Layer::get_objects() {
    return this->objs;
}

std::vector<long> Layer::get_data() {
	return this->data;
}

int Layer::get_height() const {
	return this->height;
}

int Layer::get_width() const {
	return this->width;
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