#include "Animals.h"
#include "Map.h"

void Animal::sleep() {

}

void Animal::drink(const sf::Vector2i &pos) {

}

void Animal::eat(const sf::Vector2i &pos) {

}

void Animal::move() {
    setPosition(this->path_.back());
    this->path_.pop_back();
}

Animal::Needs Animal::findOutMainNeed() {
    if (this->breed_ < this->genom_[Animal::Needs::Breed].limit) {
        return Animal::Needs::Breed;
    }
    else if (this->thirst_ < this->genom_[Animal::Needs::Drink].limit) {
        return Animal::Needs::Drink;
    }
    else if (this->hunger_ < this->genom_[Animal::Needs::Eat].limit) {
        return Animal::Needs::Eat;
    }
    else if (this->tiredness_ < this->genom_[Animal::Needs::Sleep].limit) {
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
               const int &tiredness, const int &breed, const AnimalType &type_of) : type_of_(type_of) {
    this->position_ = pos;
    this->sex_ = sex;
    this->hunger_ = hunger;
    this->thirst_ = thirst;
    this->tiredness_ = tiredness;
    this->breed_ = breed;
}

void Animal::do_things() {
    // Итерационное изменение параметров
    this->hunger_ -= this->genom_[Needs::Eat].speed;
    this->thirst_ -= this->genom_[Needs::Drink].speed;
    this->tiredness_ -= this->genom_[Needs::Sleep].speed;
    this->breed_ -= this->genom_[Needs::Breed].speed;

    // Dead?
    if (this->hunger_ < 0 ||
        this->thirst_ < 0 ||
        this->tiredness_ < 0 ||
        this->breed_ < 0) {
        this->die();
    }

    if (!this->freezed) {
        // Moving and pathworking
        if (this->main_need_ != findOutMainNeed() || this->path_.empty()) {
            this->main_need_ = findOutMainNeed();
            if (this->main_need_ == Needs::Sleep) {
                this->sleep();
                return;
            } else if (this->main_need_ == Needs::Eat) {
                sf::Vector2i end_point = Map::find(Map::Maps::entities, EntityType::food, this->position_, 1);
                Map::find_path(this->position_, end_point, this->path_);
            } else if (this->main_need_ == Needs::Drink) {
                sf::Vector2i end_point = Map::find(Map::Maps::terrain, TerrainType::river, this->position_, 1);
                Map::find_path(this->position_, end_point, this->path_);
            } else {
                sf::Vector2i end_point = Map::find(Map::Maps::animals, this->type_of_, this->position_, 1);
                Map::find_path(this->position_, end_point, this->path_);
            }
        }
        if (this->path_.size() == 1) {
            if (this->main_need_ == Needs::Breed) {
                this->breeding(this->breedable, this->path_.back());
            } else if (this->main_need_ == Needs::Eat) {
                this->eat(this->path_.back());
            } else if (this->main_need_ == Needs::Drink) {
                this->drink(this->path_.back());
            }
            this->path_.pop_back();
        }
        else {
            this->move();
        }
    }
}

Sheep::Sheep(const sf::Vector2i &pos, const Animal::SexType &sex,
             const int &hunger = 255, const int &thirst = 255, const int &tiredness = 255, const int &breed = 255)
        : Animal(pos, sex, hunger, thirst, tiredness, breed, AnimalType::Sheep) {

}

void Sheep::breeding(Animal *animal, const sf::Vector2i &pos) {

}
