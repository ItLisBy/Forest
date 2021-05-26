#ifndef FOREST_MAP_H
#define FOREST_MAP_H
#include "Animals.h"
#include <SFML/System.hpp>
#include <random>
#include <ctime>
#include <vector>
#include <queue>
#include <unordered_map>


enum EntityType {
    no_entity,
    food,
    meat
};
enum TerrainType {
    no_terrain = -1,
    forest,
    grass,
    rock,
    river
};

class Map {
public:

    enum Maps{
        terrain,
        entities,
        animals
    };

    static void init();

    /// \brief Function that spawn animals on map
    /// \param all Vector of integers. Every integer is number of animals of some type. Type depends on index
    static void spawn(const float *anim);

    static void spawn_food();

    static void place_food(const EntityType &type);

    /// \brief Find the closest entity of type T to pos
    /// \param type_find Search object
    /// \param pos From what coordinates search
    /// \param circle On what circle from pos we are searching now
    /// \return Position like a sf::Vector2i
    static sf::Vector2i find(const TerrainType &type_find, const sf::Vector2i &pos, const int &circle);
    static sf::Vector2i find(const EntityType &type_find, const sf::Vector2i &pos, const int &circle);
    static sf::Vector2i find(const AnimalType &type_find, const sf::Vector2i &pos, const int &circle);

    static void find_path(const sf::Vector2i &start, const sf::Vector2i &goal, std::vector<sf::Vector2i> &path);

    static void rm_entity(const Maps &map_type, const sf::Vector2i &pos);

    static inline void neighbors(const sf::Vector2i &curr, std::vector<sf::Vector2i> &result);

private:

    static inline double cost(const sf::Vector2i &from, const sf::Vector2i &to);

    static void a_star(const sf::Vector2i &start, const sf::Vector2i &goal,
                       std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from);

    static void reconstruct_path(const sf::Vector2i &start, const sf::Vector2i &goal, std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from,
                                 std::vector<sf::Vector2i> &path);

    static inline double heuristic(const sf::Vector2i &a, const sf::Vector2i &b);

    static int vector_length(const sf::Vector2i &vec);

public:
    static std::vector<std::vector<TerrainType>> terrain_map;
    static std::vector<std::vector<EntityType>> entities_map;
    static std::vector<std::vector<AnimalType>> animals_map;

    static std::vector<Animal*> all_animals;

    static int num_of_food;

    static const std::array<sf::Vector2i, 4> DIRS;
};

#endif //FOREST_MAP_H
