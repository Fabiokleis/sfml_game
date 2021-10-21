#include "tilemap.hpp"

bool TileMap::load(TileSet tileset, Layer layer) {
    std::string path = RESOURCE_PATH;
    path += "map/";
    if (!this->tex.loadFromFile(path + tileset.get_image())) {
        std::cerr << "ERROR on load the texture file!\n";
        return false;
    }

     // resize the vertex array to fit the level size
    this->verts.setPrimitiveType(sf::Quads);
    this->verts.resize(layer.get_width() * layer.get_height() * 4);

    std::vector<int> data = layer.get_data();

    // populate the vertex array, with one quad per tile
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] > 0) {
            // columns of sprite 32x32 / tile grid
            size_t columns = tileset.get_columns();
            size_t val = data[i] - tileset.get_firstg_id();

            // sprite position
            size_t y = floor(val / columns);
            size_t x = val % columns;

            // position on window
            size_t yPos = floor(i / layer.get_width());
            size_t xPos = i % layer.get_width();

            // get a pointer to the current tile quad
            sf::Vertex* quad = &verts[i*4];

            // 4 vertices of tile
            float xPos1 = xPos * tileset.get_tile_width();
            float xPos2 = (xPos + 1) * tileset.get_tile_width();
            float yPos1 = yPos * tileset.get_tile_height();
            float yPos2 = (yPos + 1) * tileset.get_tile_height();

            // 4 vertices of texture
            float x1 = x * tileset.get_tile_width();
            float x2 = (x + 1) * tileset.get_tile_width();
            float y1 = y * tileset.get_tile_height();
            float y2 = (y + 1) * tileset.get_tile_height();

            // set into quad the position of tile vertices
            quad[0].position = sf::Vector2f(xPos1, yPos1);
            quad[1].position = sf::Vector2f(xPos2, yPos1);
            quad[2].position = sf::Vector2f(xPos2, yPos2);
            quad[3].position = sf::Vector2f(xPos1, yPos2);

            // set into quad the position of tex vertices
            quad[0].texCoords = sf::Vector2f(x1, y1);
            quad[1].texCoords = sf::Vector2f(x2, y1);
            quad[2].texCoords = sf::Vector2f(x2, y2);
            quad[3].texCoords = sf::Vector2f(x1, y2);
        }
    }
    return true;
}
