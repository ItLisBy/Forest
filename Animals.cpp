#include "Animals.h"

void Animal::sleep() {

}

void Animal::breeding(Animal &animal) {

}

void Animal::drink() {

}

void Animal::eat() {

}

void Animal::setPosition(const sf::Vector2i &pos) {
    this->position_ = pos;
}

sf::Vector2i Animal::getPosition() {
    return position_;
}

const Animal::SexType Animal::getSex() {
    return this->sex_;
}

const Animal::Gen *Animal::getGenom() {
    return this->genom_;
}

Sheep::Sheep(const sf::Vector2i &pos, const Animal::SexType &sex, const int &hunger = 255, const int &thirst = 255,
             const int &tiredness = 255, const int &breed = 255) {
    this->position_ = pos;
    this->sex_ = sex;
    this->hunger_ = hunger;
    this->thirst_ = thirst;
    this->tiredness_ = tiredness;
    this->breed_ = breed;
}
