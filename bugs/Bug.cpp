//
// Created by Luke Hilliard on 29/03/2024.
//

#include "Bug.h"
#include <iostream>
#include <fstream>
// creation of classes in c++ followed from: https://www.w3schools.com/cpp/cpp_classes.asp

//// Getters
int Bug::getID() {return this->id;}
string Bug::getName() {return this->name;}
pair<int, int> Bug::getPosition() {return this->position;}
string Bug::getPositionString(){return "(" + to_string(this->position.first) + ", " + to_string(this->position.second) + ")";}
Direction Bug::getDirection() {return this->direction;}
list<pair<int, int>> Bug::getPath() {return this->path;}


//// Method to check if the current position is within bounds
bool Bug::isWayBlocked(pair<int, int> position) {
    return position.first >= 0 && position.first <= 10 &&
           position.second >= 0 && position.second <= 10;
}

//// Method to generate a new random direction
Direction Bug::getNewDirection() {
    return static_cast<Direction>(rand() % 4 + 1);
}







/* stop bugs from going up/down over and over
        Increasing x moves you south (down)
        Decreasing x moves you north (up)
        Increasing y moves you east (right)
        Decreasing y moves you west (left)
 x count
 y count

 if position.first = 0 || position.first = 10
    x count ++
    y count --;

if position.second = 0 || position.second = 10
    y count ++
    x count --;

if y count > 2
    random direction {EAST, WEST}

 if x count > 2
    random direction {SOUTH, NORTH}
 */


