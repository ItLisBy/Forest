#ifndef FOREST_ANIMALS_H
#define FOREST_ANIMALS_H

#include <vector>
#include "SFML/System.hpp"

enum AnimalType {
    no_animal = -1,
    Sheep,
    Wolf
};

class Animal {
public:
    enum SexType {
        female, male
    };

    enum Needs {
        Sleep,
        Breed,
        Eat,
        Drink
    };

    /// \brief Struct that represent one gene of "animals"
    /// \var speed With this speed "animals" param will decrease
    /// \var limit On this level param will influence
    struct Gen {
        int speed;
        int limit;
    };

    Animal(const sf::Vector2i &pos, const Animal::SexType &sex, const int &hunger, const int &thirst,
           const int &tiredness, const int &breed, const AnimalType &type_of);

    virtual void sleep();

    virtual void breeding(Animal *animal, const sf::Vector2i &pos) = 0;

    virtual void drink(const sf::Vector2i &pos);

    virtual void eat(const sf::Vector2i &pos);

    virtual void move();

    virtual Animal::Needs findOutMainNeed();

    virtual void setPosition(const sf::Vector2i &pos);

    sf::Vector2i getPosition();

    Animal::SexType getSex();

    Animal::Gen *getGenom();

    virtual void do_things();

    virtual void die();

    virtual void isDead();

protected:
    SexType sex_;
    Gen genom_[4];
    int breed_;
    int hunger_;
    int thirst_;
    int tiredness_;
    int speed_;
    sf::Vector2i position_;
    std::vector<sf::Vector2i> path_;
    Animal::Needs main_need_;
    const AnimalType type_of_;
    bool freezed;
    Animal* breedable;
    bool dead = false;
};

class Sheep : public Animal {
public:
    Sheep(const sf::Vector2i &pos, const Animal::SexType &sex,
          const int &hunger, const int &thirst, const int &tiredness, const int &breed);

    void breeding(Animal *animal, const sf::Vector2i &pos) override;

};

#endif //FOREST_ANIMALS_H
