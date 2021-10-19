#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "layer.hpp"
#include "tileset.hpp"
#include "tilesetmap.hpp"
#include "config.h"
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable {
	private:
		sf::VertexArray verts;
		sf::Texture tex;
		
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		states.texture = &tex;
		target.draw(verts, states);
	}
	public:
		bool load(TileSet tileset, Layer layer);

};