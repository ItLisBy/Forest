#include "Map.h"

Map::Map(const Map::TerritoryType &current_territory)
        :current_territory(current_territory) {
    terrain_map.assign(64, std::vector<int>(64, 0));
    entities_map.assign(64, std::vector<int>(64, 0));
    srand(time(nullptr));
    for (int i = 0; i < 64; ++i){
        for (int j = 0; j < 64; ++j){
            terrain_map[i][j] ((int)(rand() % 64));
        }
    }
}
