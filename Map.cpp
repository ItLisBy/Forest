#include "Map.h"

#include <random>
#include <ctime>

Map::Map(const Map::TerritoryType &current_territory)
        :current_territory(current_territory) {
    terrain_map.assign(64, std::vector<int>(64, 0));
    entities_map.assign(64, std::vector<int>(64, 0));
    srand(time(0));
    for (int i = 0; i < 64; ++i){
        for (int j = 0; j < 64; ++j){
            terrain_map[i][j] = rand() % 64;
        }
    }
}
void Map::Spawn(const int &all, const float &meat_to_all) {
    srand(time(0) * 10);
    for (int i = 0; i < all; ++i){
        int place = rand() % 4096;
        Animal::AnimalsType type = RandAnimal(meat_to_all);
        this->entities_map[place / 64][place % 64] = type;
    }
}

Animal::AnimalsType Map::RandAnimal(const float &meat_to_all) {
    if (meat_to_all < 1){
        if ((rand() % 100) > 100*meat_to_all){
            return Animal::AnimalsType::Sheep;
        }
        else {
            return Animal::AnimalsType::Wolf;
        }
    }
    return Animal::AnimalsType::None;
}
