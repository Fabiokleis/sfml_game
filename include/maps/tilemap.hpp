#ifndef TILEMAP_HPP_MNF5HXD8
#define TILEMAP_HPP_MNF5HXD8
#include <SFML/Graphics.hpp>
#include <cmath>
#include "layer.hpp"
#include "tileset.hpp"
#include "tilesetmap.hpp"
#include "config.h"
#include <iostream>

namespace Maps {

    class TileMap : public sf::Drawable, public sf::Transformable {
    	private:
    		sf::VertexArray verts;
    		sf::Texture tex;
    		
    	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    		states.transform *= getTransform();
    		states.texture = &tex;
    		target.draw(verts, states);
    	}
    	public:
    		bool load(TileSet tileset, Layer &layer);
    };
}
#endif /* end of include guard: TILEMAP_HPP_MNF5HXD8 */
