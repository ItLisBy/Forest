#ifndef FOREST_MAP_H
#define FOREST_MAP_H

#include <vector>
#include <random>
#include <ctime>

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
private:
    const TerritoryType current_territory;
    std::vector<std::vector<int>> terrain_map;
    std::vector<std::vector<int>> entities_map;
};


#endif //FOREST_MAP_H
