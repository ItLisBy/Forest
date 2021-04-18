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
    void spawn(const std::vector<int> &all);

    /// \brief Find the closest entity of type T to pos
    /// \tparam T Type of entity to find
    /// \param map_type Type of map in which to find
    /// \param type_find Search object
    /// \param pos From what coordinates search
    /// \param circle On what circle from pos we are searching now
    /// \return Position like a sf::Vector2i
    template<typename T>
    sf::Vector2i find(const Maps &map_type, const T &type_find, const sf::Vector2i &pos, const int &circle);

    void neighbors(const sf::Vector2i &curr, std::vector<sf::Vector2i> &result, const Map &map);

    double cost(const sf::Vector2i &from, const sf::Vector2i &to);

    void a_star(const sf::Vector2i &start, const sf::Vector2i &goal,
                std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from, const Map &map);

    void reconstruct_path(sf::Vector2i start, sf::Vector2i goal, std::unordered_map<sf::Vector2i, sf::Vector2i> &came_from,
                          std::vector<sf::Vector2i> &path);

    inline double heuristic(const sf::Vector2i &a, const sf::Vector2i &b);

    void find_path(const sf::Vector2i start, const sf::Vector2i goal, std::vector<sf::Vector2i> &path, const Map &map);

private:
    /// Define what set of textures should we use
    const TerritoryType current_territory;

    std::vector<std::vector<TerrainType>> terrain_map;
    std::vector<std::vector<EntityType>> entities_map;
    std::vector<std::vector<AnimalType>> animals_map;

    std::array<sf::Vector2i, 8> DIRS {sf::Vector2i(1, 0),
                                      sf::Vector2i(0, -1),
                                      sf::Vector2i(-1, 0),
                                      sf::Vector2i(0, 1)};
};

#endif //FOREST_MAP_H
