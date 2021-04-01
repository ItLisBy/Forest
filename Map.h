#ifndef FOREST_MAP_H
#define FOREST_MAP_H
#include "Animals.h"
#include <SFML/System.hpp>
#include <random>
#include <ctime>
#include <vector>

enum EntityType {
    no_entity,
    food,
    water
};

class Map {
public:
    enum TerritoryType {
        middle_forest,
        jungle
    };
    enum TerrainType {
        no_terrain = -1,
        grass,
        forest,
        river,
        rock
    };
    enum Maps{
        terrain,
        entities,
        animals
    };

    Map(const Map::TerritoryType &current_territory);

    /// \brief Function that spawn animals on map
    /// \param all Vector of integers. Every integer is number of animals of some type. Type depends on index
    void Spawn(const std::vector<int> &all);

    /// \brief Find the closest entity of type T to pos
    /// \tparam T Type of entity to find
    /// \param map_type Type of map in which to find
    /// \param type_find Search object
    /// \param pos From what coordinates search
    /// \param circle On what circle from pos we are searching now
    /// \return Position like a sf::Vector2i
    template<typename T>
    sf::Vector2i find(const Maps &map_type, const T &type_find, const sf::Vector2i &pos, const int &circle);

private:
    /// Define what set of textures should we use
    const TerritoryType current_territory;

    std::vector<std::vector<TerrainType>> terrain_map;
    std::vector<std::vector<EntityType>> entities_map;
    std::vector<std::vector<AnimalType>> animals_map;
};


#endif //FOREST_MAP_H
