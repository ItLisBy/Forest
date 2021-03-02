#ifndef FOREST_ANIMALS_H
#define FOREST_ANIMALS_H

#include "SFML/System.hpp"

class Animal {
public:
    enum SexType {female, male};

    struct Gen {
        int speed;
        int limit;
    };

    virtual void sleep();
    virtual void breeding(Animal &animal);
    virtual void drink();
    virtual void eat();
    virtual void setPosition(const sf::Vector2i &pos);
    virtual sf::Vector2i getPosition();

    const SexType getSex();
    const Gen* getGenom();

protected:
    SexType sex_;
    Gen genom_[4];
    int breed_;
    int hunger_;
    int thirst_;
    int tiredness_;
    sf::Vector2i position_;
};

class Sheep : public Animal{
public:
    Sheep(const sf::Vector2i &pos, const Animal::SexType &sex, const int &hunger, const int &thirst,
          const int &tiredness, const int &breed);
};
#endif //FOREST_ANIMALS_H
