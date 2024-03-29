#ifndef FOREST_ANIMALS_H
#define FOREST_ANIMALS_H

#include <vector>
#include "SFML/System.hpp"

#define NUM_ANIMALS 3

enum AnimalType {
    no_animal,
    TSheep,
    TWolf,
    THare
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

    virtual void breeding(const sf::Vector2i &pos);

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

    virtual bool isDead();

    AnimalType getType();

protected:
    SexType sex_ = SexType::female;
    Gen genom_[4] = {
            {5, 35},
            {5, 40},
            {8, 80},
            {5, 80}
    };
    int breed_ = 0;
    int hunger_ = 0;
    int thirst_ = 0;
    int tiredness_ = 0;
    int live_ = 1000;
    sf::Vector2i position_;
    std::vector<sf::Vector2i> path_;
    Animal::Needs main_need_ = Animal::Needs::Sleep;
    const AnimalType type_of_ = AnimalType::no_animal;
    bool freezed = false;
    bool dead = false;
    static const unsigned short int MAX_VALUE_OF_NEED = 100;
};

class Sheep : public Animal {
public:
    Sheep(const sf::Vector2i &pos, const Animal::SexType &sex, const int &hunger, const int &thirst, const int &tiredness, const int &breed);

    //void breeding(const sf::Vector2i &pos) override;

};

class Wolf : public Animal {
public:
    Wolf(const sf::Vector2i &pos, const Animal::SexType &sex,
          const int &hunger, const int &thirst, const int &tiredness, const int &breed);

    //void breeding(const sf::Vector2i &pos) override;

};

class Hare : public Animal {
public:
    Hare(const sf::Vector2i &pos, const Animal::SexType &sex,
          const int &hunger, const int &thirst, const int &tiredness, const int &breed);

    //void breeding(const sf::Vector2i &pos) override;

};

#endif //FOREST_ANIMALS_H
