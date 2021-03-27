#include <iostream>
#include "Map.h"


int vector_length(const sf::Vector2i &vec){
    return sqrt((vec.x*vec.x) + (vec.y*vec.y));
}

Map::Map(const Map::TerritoryType &current_territory)
        :current_territory(current_territory) {
    // Initialize all maps
    terrain_map.assign(64, std::vector<TerrainType>(64, TerrainType::no_terrain));
    entities_map.assign(64, std::vector<EntityType>(64, EntityType::no_entity));
    animals_map.assign(64, std::vector<AnimalType>(64, AnimalType::no_animal));

    // Generate terrain Voronoi map
    // Generate centers
    const short NUM_CENTERS = 32;
    std::vector<int> centers(NUM_CENTERS, 0);
    srand(time(0));
    for (int i = 0; i < NUM_CENTERS; ++i) {
        centers[i] = rand() % 4096;
        int terr = rand() % 10;
        terrain_map[centers[i] / 64][centers[i] % 64] = TerrainType(terr > 6 ? terr == 9 ? 3 : 2 : terr > 3 ? 1 : 0);
    }

    // Fill map
    for (int i = 0; i < terrain_map.size(); ++i) {
        for (int j = 0; j < terrain_map[i].size(); ++j) {
            sf::Vector2i min(centers[0] % 64, centers[0] / 64);
            sf::Vector2i curr(j, i);
            for (auto c : centers) { // Which center is the closest
                if (vector_length(curr - sf::Vector2i(c % 64, c / 64)) < vector_length(curr - min)) {
                    min = sf::Vector2i(c % 64, c / 64);
                }
            }
            terrain_map[i][j] = terrain_map[min.y][min.x];
        }
    }

    for (int i = 0; i < terrain_map.size(); ++i) {
        for (int j = 0; j < terrain_map[i].size(); ++j) {
            std::cout << terrain_map[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void Map::Spawn(const std::vector<int> &all) {
    srand(time(0));
    for (int i = 0; i < all.size(); ++i) {
        for (int j = 0; j < all[i]; ++j) {
            int pos = rand() % 4096;
            if (terrain_map[pos / 64][pos % 64] != TerrainType::river &&
                terrain_map[pos / 64][pos % 64] != TerrainType::rock &&
                entities_map[pos / 64][pos % 64] == EntityType::no_entity) {
                animals_map[pos / 64][pos % 64] = AnimalType(i);
            }
            else {
                j -= 1;
            }
        }
    }
}

template<typename T>
sf::Vector2i Map::find(const Map::Maps &map_type, const T &type_find, const sf::Vector2i &pos) {
    std::vector<std::vector<T>>* map;
    if (map_type == Maps::terrain) {
        map = &terrain_map;
    }
    else if (map_type == Maps::entities) {
        map = &entities_map;
    }
    else if (map_type == Maps::animals) {
        map = &animals_map;
    }
    // Find first from pos
    for (int i = pos.y; i < map->size(); ++i) {
        for (int j = pos.x; j < map[i].size(); ++j) {
            if (map[i][j] == type_find) {
                return sf::Vector2i(j, i);
            }
        }
    }
    return sf::Vector2i(-1, -1);
}

