#include "Animals.h"
#include "Map.h"

void Animal::sleep() {
    this->tiredness_ = MAX_VALUE_OF_NEED;
}

void Animal::drink(const sf::Vector2i &pos) {
    this->thirst_ += this->genom_[Needs::Drink].limit;
}

void Animal::eat(const sf::Vector2i &pos) {
    this->hunger_ += this->genom_[Needs::Eat].limit;
    Map::rm_entity(Map::Maps::entities, pos);
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
    else {
        return Animal::Needs::Sleep;
    }
}

void Animal::setPosition(const sf::Vector2i &pos) {
    Map::animals_map[this->position_.y][this->position_.x] = AnimalType::no_animal;
    try {
        this->position_ = pos;
    }
    catch (...){

    }
    Map::animals_map[this->position_.y][this->position_.x] = this->getType();
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
    this->live_ -= 1;

    // Dead?
    if (this->hunger_ < 0 ||
        this->thirst_ < 0 ||
        this->tiredness_ < 0 ||
        this->breed_ < 0 ||
        this->live_ < 0) {
        this->die();
    }

    if (!this->freezed) {
        // Moving and pathworking
        if (this->path_.empty() || this->main_need_ != findOutMainNeed()) {
            this->main_need_ = findOutMainNeed();
            if (this->main_need_ == Needs::Sleep) {
                this->sleep();
                return;
            } else if (this->main_need_ == Needs::Eat) {
                sf::Vector2i end_point = Map::find(this->getType() == AnimalType::TWolf ? EntityType::meat : EntityType::food, this->position_, 1);
                Map::find_path(this->position_, end_point, this->path_);
            } else if (this->main_need_ == Needs::Drink) {
                sf::Vector2i end_point = Map::find(TerrainType::river, this->position_, 1);
                Map::find_path(this->position_, end_point, this->path_);
            } else {
                this->breeding(this->position_);
                return;
            }
        }
        if (this->path_.size() == 1) {
            if (this->main_need_ == Needs::Eat) {
                this->eat(this->path_.back());
            } else if (this->main_need_ == Needs::Drink) {
                this->drink(this->path_.back());
            }
            this->path_.pop_back();
        }
        else {
            if (this->main_need_ == Needs::Sleep) {
                this->sleep();
            }
            else if (this->main_need_ == Needs::Breed){
                this->breeding(this->position_);
            }
            else {
                if (!this->path_.empty())
                    this->move();
            }
        }
    }
}

void Animal::die() {
    Map::animals_map[this->position_.y][this->position_.x] = AnimalType::no_animal;
    int pos = 0;
    for (int i = 0; i < Map::all_animals.size(); ++i) {
        if (Map::all_animals[i] == this) {
            pos = i;
        }
    }
    Map::all_animals.erase(Map::all_animals.begin() + pos);
}

bool Animal::isDead() {
    return this->dead;
}

AnimalType Animal::getType() {
    return this->type_of_;
}

void Animal::breeding(const sf::Vector2i &pos) {
    Animal* tmp_a;
    srand(time(0));
    if (this->getType() == AnimalType::TSheep) {
        tmp_a = new Sheep(this->position_,
                          (rand() % 2 ? Animal::SexType::female : Animal::SexType::male),
                          100, 100, 100, 100);
    }
    else if (this->getType() == AnimalType::TWolf) {
        tmp_a = new Wolf(this->position_,
                          (rand() % 2 ? Animal::SexType::female : Animal::SexType::male),
                          100, 100, 100, 100);
    }
    else if (this->getType() == AnimalType::THare) {
        tmp_a = new Hare(this->position_,
                         (rand() % 2 ? Animal::SexType::female : Animal::SexType::male),
                         100, 100, 100, 100);
    }
    Map::all_animals.push_back(tmp_a);
    Map::animals_map[this->position_.y][this->position_.x] = this->getType();
    this->breed_ += this->genom_[Needs::Breed].limit;
}

Sheep::Sheep(const sf::Vector2i &pos, const Animal::SexType &sex,
              const int &hunger = MAX_VALUE_OF_NEED, const int &thirst = MAX_VALUE_OF_NEED,
              const int &tiredness = MAX_VALUE_OF_NEED, const int &breed = MAX_VALUE_OF_NEED)
        : Animal(pos, sex, hunger, thirst, tiredness, breed, AnimalType::TSheep) {

}

Wolf::Wolf(const sf::Vector2i &pos, const Animal::SexType &sex,
           const int &hunger = MAX_VALUE_OF_NEED, const int &thirst = MAX_VALUE_OF_NEED,
           const int &tiredness = MAX_VALUE_OF_NEED, const int &breed = MAX_VALUE_OF_NEED)
        : Animal(pos, sex, hunger, thirst, tiredness, breed, AnimalType::TWolf) {

}

Hare::Hare(const sf::Vector2i &pos, const Animal::SexType &sex,
           const int &hunger = MAX_VALUE_OF_NEED, const int &thirst = MAX_VALUE_OF_NEED,
           const int &tiredness = MAX_VALUE_OF_NEED, const int &breed = MAX_VALUE_OF_NEED)
        : Animal(pos, sex, hunger, thirst, tiredness, breed, AnimalType::THare) {

}
