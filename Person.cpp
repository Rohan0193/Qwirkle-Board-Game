#include "Person.h"


Person::Person(std::string name, std::shared_ptr<LinkedList>, int points){ 
    this->name = name;
    this->hand = hand;
    this->points = points;  
}

Person::~Person(){
}

Person::Person(const Person& other){

    name = other.name;
    hand = other.hand;
    points = other.points;
}

std::string Person::getName(){
    return name;
}

std::shared_ptr<LinkedList> Person::getHand(){
    return hand;
}

int Person::getPoints(){
    return points;
}

void Person::setName(std::string name){
    this -> name = name;
}

void Person::setHand(std::shared_ptr<LinkedList> hand){
    this -> hand = hand;
}

void Person::setPoints(int points){
    this -> points += points;
}