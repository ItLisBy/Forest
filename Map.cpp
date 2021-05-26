#include <iostream>
#include "Map.h"

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<sf::Vector2i> {
        typedef sf::Vector2i argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const sf::Vector2i& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

std::vector<std::vector<TerrainType>> Map::terrain_map;
std::vector<std::vector<EntityType>> Map::entities_map;
std::vector<std::vector<AnimalType>> Map::animals_map;
std::vector<Animal*> Map::all_animals;
int Map::num_of_food = 100;

const std::array<sf::Vector2i, 4> Map::DIRS =  {sf::Vector2i(1, 0),
                                                sf::Vector2i(0, -1),
                                                sf::Vector2i(-1, 0),
                                                sf::Vector2i(0, 1)};

int Map::vector_length(const sf::Vector2i &vec){
    return sqrt((vec.x*vec.x) + (vec.y*vec.y));
}

void Map::init() {
    // Initialize all maps
    Map::terrain_map.assign(64, std::vector<TerrainType>(64, TerrainType::no_terrain));
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
/*
    for (int i = 0; i < terrain_map.size(); ++i) {
        for (int j = 0; j < terrain_map[i].size(); ++j) {
            std::cout << terrain_map[i][j] << " ";
        }
        std::cout << std::endl;
    }*/

}

void Map::spawn(const float *anim) {
    srand(time(0));
    int pos;
    Animal* tmp_a;
    for (int i = 1; i < NUM_ANIMALS + 1; ++i) {
        for(int j = 0; j < anim[i]; ++j) {
            pos = rand() % 4096;
            if (terrain_map[pos / 64][pos % 64] != TerrainType::river &&
                terrain_map[pos / 64][pos % 64] != TerrainType::rock &&
                entities_map[pos / 64][pos % 64] == EntityType::no_entity) {
                if (i == AnimalType::TSheep) {
                    tmp_a = new Sheep(sf::Vector2i(pos % 64, pos / 64),
                                           (rand() % 2 ? Animal::SexType::female : Animal::SexType::male),
                                           100, 100, 100, 100);
                }
                else if (i == AnimalType::TWolf) {
                    tmp_a = new Wolf(sf::Vector2i(pos % 64, pos / 64),
                                      (rand() % 2 ? Animal::SexType::female : Animal::SexType::male),
                                      100, 100, 100, 100);
                }
                else if (i == AnimalType::THare) {
                    tmp_a = new Hare(sf::Vector2i(pos % 64, pos / 64),
                                      (rand() % 2 ? Animal::SexType::female : Animal::SexType::male),
                                      100, 100, 100, 100);
                }
                animals_map[pos / 64][pos % 64] = tmp_a->getType();
                all_animals.push_back(tmp_a);
            }
            else {
                --j;
            }
        }
    }
}


sf::Vector2i Map::find(const TerrainType &type_find, const sf::Vector2i &pos, const int &circle) {
    srand(time(0));
    if (circle > 30) {
        std::vector<sf::Vector2i> curr_neighbours;
        Map::neighbors(pos, curr_neighbours);
        return curr_neighbours[rand() % curr_neighbours.size()];
    }

    std::vector<sf::Vector2i> on_circle;
    sf::Vector2i current_pos = pos - sf::Vector2i(circle, circle);
    short roots[] =  {0, 1, 0, -1, 0};

    // 4 is number of "sides" of circle that we should inspect
    for (int i = 0; i < 4; ++i) {
        int delta_y = roots[i];
        int delta_x = roots[i+1];

        for (int j = 0; j < circle*2; ++j) {
            if (current_pos.x < 64 && current_pos.y < 64 &&
            current_pos.x >=0 && current_pos.y >= 0) {
                if (terrain_map[current_pos.y][current_pos.x] == type_find) {
                    on_circle.emplace_back(current_pos.x, current_pos.y);
                }
            }
            current_pos += sf::Vector2i(delta_x, delta_y);
        }
    }

    // If entities not found then go to the next circle
    if (on_circle.empty()) {
        return find(type_find, pos, circle + 1);
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

sf::Vector2i Map::find(const EntityType &type_find, const sf::Vector2i &pos, const int &circle) {
    srand(time(0));
    if (circle > 30) {
        std::vector<sf::Vector2i> curr_neighbours;
        Map::neighbors(pos, curr_neighbours);
        return curr_neighbours[rand() % curr_neighbours.size()];
    }

    std::vector<sf::Vector2i> on_circle;
    sf::Vector2i current_pos = pos - sf::Vector2i(circle, circle);
    short roots[] =  {0, 1, 0, -1, 0};

    // 4 is number of "sides" of circle that we should inspect
    for (int i = 0; i < 4; ++i) {
        int delta_y = roots[i];
        int delta_x = roots[i+1];

        for (int j = 0; j < circle*2; ++j) {
            if (current_pos.x < 64 && current_pos.y < 64 &&
                current_pos.x >=0 && current_pos.y >= 0) {
                if (entities_map[current_pos.y][current_pos.x] == type_find) {
                    on_circle.emplace_back(current_pos.x, current_pos.y);
                }
            }
            current_pos += sf::Vector2i(delta_x, delta_y);
        }
    }

    // If entities not found then go to the next circle
    if (on_circle.empty()) {
        return find(type_find, pos, circle + 1);
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

sf::Vector2i Map::find(const AnimalType &type_find, const sf::Vector2i &pos, const int &circle) {
    srand(time(0));
    if (circle > 30) {
        std::vector<sf::Vector2i> curr_neighbours;
        Map::neighbors(pos, curr_neighbours);
        return curr_neighbours[rand() % curr_neighbours.size()];
    }

    std::vector<sf::Vector2i> on_circle;
    sf::Vector2i current_pos = pos - sf::Vector2i(circle, circle);
    short roots[] =  {0, 1, 0, -1, 0};

    // 4 is number of "sides" of circle that we should inspect
    for (int i = 0; i < 4; ++i) {
        int delta_y = roots[i];
        int delta_x = roots[i+1];

        for (int j = 0; j < circle*2; ++j) {
            if (current_pos.x < 64 && current_pos.y < 64 &&
                current_pos.x >=0 && current_pos.y >= 0) {
                if (animals_map[current_pos.y][current_pos.x] == type_find) {
                    on_circle.emplace_back(current_pos.x, current_pos.y);
                }
            }
            current_pos += sf::Vector2i(delta_x, delta_y);
        }

    }

    // If entities not found then go to the next circle
    if (on_circle.empty()) {
        return find(type_find, pos, circle + 1);
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
    result.erase(result.begin(), result.end());
    for (auto &dir : DIRS) {
        sf::Vector2i next(curr.x + dir.x, curr.y + dir.y);
        if (next.x < 64 && next.y < 64 &&
            next.x >= 0 && next.y >= 0 &&
            Map::terrain_map[next.y][next.x] < 2 && Map::terrain_map[next.y][next.x] != -1) {
            result.push_back(next);
        }
    }
}

double Map::cost(const sf::Vector2i &from, const sf::Vector2i &to) {
    return ((to - from).x || (to - from).y) ? 2 : 1;
}

void Map::a_star(const sf::Vector2i &start, const sf::Vector2i &goal,
                 std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from) {

    auto my_comp =
            [](const std::pair<sf::Vector2i, double> &e1, const std::pair<sf::Vector2i, double> &e2)
            { return e1.second > e2.second; };

    std::vector<sf::Vector2i> curr_neighbours;
    std::unordered_map<sf::Vector2i, double> cost_so_far;
    std::priority_queue<std::pair<sf::Vector2i, double>, std::vector<std::pair<sf::Vector2i, double>>, decltype(my_comp)> frontier(my_comp);
    frontier.push(std::make_pair(start, 0));

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        auto current = frontier.top().first;
        frontier.pop();

        if (current == goal) {
            break;
        }

        neighbors(current, curr_neighbours);
        for (auto& next : curr_neighbours) {
            double new_cost = cost_so_far[current] + cost(current, next);
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.push(std::make_pair(next, priority));
                came_from[next] = current;
            }
        }
    }
}

double Map::heuristic(const sf::Vector2i &a, const sf::Vector2i &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void Map::reconstruct_path(const sf::Vector2i &start, const sf::Vector2i &goal, std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from,
                           std::vector<sf::Vector2i> &path) {
    sf::Vector2i current = goal;
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    //std::reverse(path.begin(), path.end());
}

void Map::find_path(const sf::Vector2i &start, const sf::Vector2i &goal, std::vector<sf::Vector2i> &path) {
    std::unordered_map<sf::Vector2i, sf::Vector2i> came_from;
    path.clear();
    a_star(start, goal, came_from);
    reconstruct_path(start, goal, came_from, path);
}

void Map::rm_entity(const Map::Maps &map_type, const sf::Vector2i &pos) {
    if (map_type == Maps::entities) {
        entities_map[pos.y][pos.x] = no_entity;
        Map::num_of_food--;
    }
    else if (map_type == Maps::animals) {
        animals_map[pos.y][pos.x] = no_animal;
        for (auto &an : all_animals) {
            if (an->getPosition() == pos) {
                an->die();
            }
        }
    }
}

void Map::spawn_food() {
    srand(time(0));
    int pos;
    EntityType type;
    for (int i = 0; i < num_of_food; ++i) {
        if (i < num_of_food / 2)
            type = EntityType::food;
        else
            type = EntityType::meat;
        pos = rand() % 4096;
        if (terrain_map[pos / 64][pos % 64] != TerrainType::river &&
            terrain_map[pos / 64][pos % 64] != TerrainType::rock &&
            entities_map[pos / 64][pos % 64] == EntityType::no_entity &&
            animals_map[pos / 64][pos % 64] == AnimalType::no_animal) {
            entities_map[pos / 64][pos % 64] = type;
        }
        else {
            --i;
        }
    }
}

void Map::place_food(const EntityType &type) {
    srand(time(0));
    int pos;
    while (true){
        pos = rand() % 4096;
        if (terrain_map[pos / 64][pos % 64] != TerrainType::river &&
            terrain_map[pos / 64][pos % 64] != TerrainType::rock &&
            entities_map[pos / 64][pos % 64] == EntityType::no_entity &&
            animals_map[pos / 64][pos % 64] == AnimalType::no_animal) {
            entities_map[pos / 64][pos % 64] = type;
            ++num_of_food;
            break;
        }
    }

}

