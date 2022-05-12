#ifndef PERSON_H
#define PERSON_H

#include "LinkedList.h"

#include <memory>

class Person {
public:

   Person(std::string name, std::shared_ptr<LinkedList> hand, int points);
   ~Person();
   Person(const Person& other);
   std::string getName();
   std::shared_ptr<LinkedList> getHand();
   int getPoints();
   void setName(std::string name);
   void setHand(std::shared_ptr<LinkedList> hand);
   void setPoints(int points);

private:
   std::string name;
   std::shared_ptr<LinkedList> hand;
   int points;
};

#endif