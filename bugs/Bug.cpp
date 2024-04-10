//
// Created by Luke Hilliard on 29/03/2024.
//

#include "Bug.h"
// creation of classes in c++ followed from: https://www.w3schools.com/cpp/cpp_classes.asp

//// Getters
int Bug::getID() {return this->id;}

Direction Bug::getDirection() {return this->direction;}


//// Method to check if the current position is within bounds
bool Bug::isWayBlocked(pair<int, int> position) {
    return position.first >= 0 && position.first <= 10 &&
           position.second >= 0 && position.second <= 10;
}

//// Method to generate a new random direction
Direction getNewDirection() {
    return static_cast<Direction>(rand() % 4 + 1);
}