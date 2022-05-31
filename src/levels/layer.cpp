#include "layer.hpp"
using namespace Levels;

Layer::Layer(rapidjson::Value& value) : tiles(), walls(), platforms() {
    // in case the layer type is tilelayer
	if (value.HasMember("data")) {
		for (auto& i : value["data"].GetArray()) {
			this->data.push_back(i.GetInt64());
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

    init_object_layers(value);

}
void Layer::init_object_layers(rapidjson::Value& value) {
    // case a layer of objects
    if (value.HasMember("objects")) {
        // pass all informations parsed to be a new location obj
        if (this->name == "locations") {
            this->locations = Locations(value);

        } else if (this->name == "platforms") { // pass all informations parsed to be a new platform obj
            this->platforms = Platforms(value);

        } else if (this->name == "tiles") { // pass all informations parsed to be a new tile obj
            this->tiles = Tiles(value);

        } else if (this->name == "walls") {  // pass all informations parsed to be a new wall obj
            this->walls = Walls(value);
        }
    }
}
Locations Layer::get_locations() {
    return this->locations;
}

Tiles Layer::get_tiles() {
    return this->tiles;
}

Platforms Layer::get_platforms() {
    return this->platforms;
}

Walls Layer::get_walls() {
    return this->walls;
}

Layer::Layer() : name(), type(), width(), height(), tiles(), walls(), platforms() {}

Layer::~Layer() = default;

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