#ifndef FOREST_MAP_H
#define FOREST_MAP_H
#include "Animals.h"
#include <random>
#include <ctime>
#include <vector>

class Map {
public:
    enum TerritoryType {
        middle_forest,
        jungle
    };
    enum TerrainTypes {
        grass,
        forest,
        river,
        rock
    };
    Map(const Map::TerritoryType &current_territory);
    void Spawn(const int &all, const float &meat_to_all);
private:
    const TerritoryType current_territory;
    std::vector<std::vector<int>> terrain_map;
    std::vector<std::vector<int>> entities_map;
    Animal::AnimalsType RandAnimal(const float &meat_to_all);
};


#endif //FOREST_MAP_H
