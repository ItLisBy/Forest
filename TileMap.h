#ifndef FOREST_TILEMAP_H
#define FOREST_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Map.h"


class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<TerrainType>> &tiles, unsigned int width, unsigned int height);
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<AnimalType>> &tiles, unsigned int width, unsigned int height);
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<std::vector<EntityType>> &tiles, unsigned int width, unsigned int height);

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


#endif //FOREST_TILEMAP_H
