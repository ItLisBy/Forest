#ifndef FOREST_ANIMALS_H
#define FOREST_ANIMALS_H

#include "SFML/System.hpp"

class Animal {
public:
    enum SexType {
        female, male
    };

    /// \brief Struct that represent one gene of "animal"
    /// \var speed With this speed "animal" param will decrease
    /// \var limit On this level param will influence
    struct Gen {
        int speed;
        int limit;
    };

    Animal (const sf::Vector2i &pos, const Animal::SexType &sex, const int &hunger, const int &thirst,
            const int &tiredness, const int &breed);

    virtual void sleep();

    virtual void breeding(Animal* animal) = 0;

    virtual void drink();

    virtual void eat();

    virtual void setPosition(const sf::Vector2i &pos);

    sf::Vector2i getPosition();

    Animal::SexType getSex();

    Animal::Gen *getGenom();

protected:
    SexType sex_;
    Gen genom_[4];
    int breed_;
    int hunger_;
    int thirst_;
    int tiredness_;
    sf::Vector2i position_;
};

class Sheep : public Animal {
public:
    Sheep(const sf::Vector2i &pos, const Animal::SexType &sex,
          const int &hunger, const int &thirst, const int &tiredness, const int &breed);

    void breeding(Animal* animal) override;
};

#endif //FOREST_ANIMALS_H
