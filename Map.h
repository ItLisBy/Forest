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
    water,

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
    void Spawn(const std::vector<int> &all);

    template<typename T>
    sf::Vector2i find(const Maps &map_type, const T &type_find, const sf::Vector2i &pos);

private:
    const TerritoryType current_territory;
    std::vector<std::vector<TerrainType>> terrain_map;
    std::vector<std::vector<EntityType>> entities_map;
    std::vector<std::vector<AnimalType>> animals_map;
};


#endif //FOREST_MAP_H
