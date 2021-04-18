#include <iostream>
#include "Map.h"

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<sf::Vector2i> {
        typedef sf::Vector2i argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const Vector2i& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

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
sf::Vector2i Map::find(const Maps &map_type, const T &type_find, const sf::Vector2i &pos, const int &circle) {
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

    std::vector<sf::Vector2i> on_circle;
    sf::Vector2i current_pos = pos - sf::Vector2i(circle, circle);
    short roots[] =  {0, 1, 0, -1, 0};

    // 4 is number of "sides" of circle that we should inspect
    for (int i = 0; i < 4; ++i) {
        int delta_y = roots[i];
        int delta_x = roots[i+1];

        for (int j = 0; j < circle*2; ++j) {
            if (map[current_pos.y][current_pos.x] == type_find) {
                on_circle.push_back(sf::Vector2i(current_pos.x, current_pos.y));
            }
            current_pos += sf::Vector2i(delta_x, delta_y);
        }
    }

    // If entities not found then go to the next circle
    if (on_circle.empty()) {
        return find(map_type, type_find, pos, circle + 1);
    }
    else {
        sf::Vector2i min = on_circle[0];
        for (auto p : on_circle) {
            if (vector_length(pos - p) < vector_length(pos - min)) {
                min = p;
            }
        }
        return min;
    }

}

void Map::neighbors(const sf::Vector2i &curr, std::vector<sf::Vector2i> &result) {
    for (auto &dir : DIRS) {
        sf::Vector2i next(curr.x + dir.x, curr.y + dir.y);
        if (terrain_map[next.y][next.x] < 2 && terrain_map[next.y][next.x] != -1) {
            result.push_back(next);
        }
    }
}

double Map::cost(const sf::Vector2i &from, const sf::Vector2i &to) {
    return ((to - from).x || (to - from).y) ? 2 : 1;
}

void Map::a_star(const sf::Vector2i start, const sf::Vector2i goal,
                 std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from) {
    std::vector<sf::Vector2i> curr_neighbours;
    std::unordered_map<sf::Vector2i, double> cost_so_far;
    PriorityQueue<sf::Vector2i, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        auto current = frontier.get();

        if (current == goal) {
            break;
        }
        neighbors(current, curr_neighbours);
        for (auto& next : curr_neighbours) {
            double new_cost = cost_so_far[current] + cost(current, next);
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}

double Map::heuristic(const sf::Vector2i &a, const sf::Vector2i &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector<sf::Vector2i> Map::reconstruct_path(sf::Vector2i start, sf::Vector2i goal,
                                                std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from) {
    std::vector<sf::Vector2i> path;
    sf::Vector2i current = goal;
    path.push_back(current);
    while (current != start) {
        current = came_from[current];
        path.push_back(current);
    }
    path.push_back(start); // необязательно
    std::reverse(path.begin(), path.end());
    return path;
}

