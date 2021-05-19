#include "Animals.h"

void Animal::sleep() {

}

void Animal::drink() {

}

void Animal::eat() {

}

void Animal::move() {
    Animal::Needs main_need = this->findOutMainNeed();

}

Animal::Needs Animal::findOutMainNeed() {
    if (breed_ < genom_[Animal::Needs::Breed].limit) {
        return Animal::Needs::Breed;
    }
    else if (thirst_ < genom_[Animal::Needs::Drink].limit) {
        return Animal::Needs::Drink;
    }
    else if (hunger_ < genom_[Animal::Needs::Eat].limit) {
        return Animal::Needs::Eat;
    }
    else if (tiredness_ < genom_[Animal::Needs::Sleep].limit) {
        return Animal::Needs::Sleep;
    }

}

void Animal::setPosition(const sf::Vector2i &pos) {
    this->position_ = pos;
}

sf::Vector2i Animal::getPosition() {
    return this->position_;
}

Animal::SexType Animal::getSex() {
    return this->sex_;
}

Animal::Gen *Animal::getGenom() {
    return this->genom_;
}

Animal::Animal(const sf::Vector2i &pos, const Animal::SexType &sex, const int &hunger, const int &thirst,
               const int &tiredness, const int &breed) {
    this->position_ = pos;
    this->sex_ = sex;
    this->hunger_ = hunger;
    this->thirst_ = thirst;
    this->tiredness_ = tiredness;
    this->breed_ = breed;
}

Sheep::Sheep(const sf::Vector2i &pos, const Animal::SexType &sex,
             const int &hunger = 255, const int &thirst = 255, const int &tiredness = 255, const int &breed = 255)
        : Animal(pos, sex, hunger, thirst, tiredness, breed) {

}

void Sheep::breeding(Animal *animal) {

}
