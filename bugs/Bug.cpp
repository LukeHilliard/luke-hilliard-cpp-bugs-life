//
// Created by Luke Hilliard on 17/04/2024.
//

#include "Bug.h"
//// Getters
int Bug::getId() { return this->id; }
string Bug::getName() { return this->name; }
int Bug::getSize() { return this->size; }
bool Bug::isAlive() { return this->alive; }
pair<int, int> Bug::getPosition() { return this->position; }
Direction Bug::getDirection() { return this->direction; }
list<pair<int, int>>& Bug::getPath() { return this->path; }
int Bug::getPathSize() { return this->path.size(); }

//// Setters
void Bug::eat(int sizeToIncreaseBy) { this->size += sizeToIncreaseBy; }
void Bug::setAlive(bool newBugState) { this->alive = newBugState; }

//// Helper methods
bool Bug::isWayBlocked(pair<int, int> &position) {
    if((position.first < 0 || position.second > 9) ||
            (position.first > 9 || position.second < 0))
        return true; // position is within bounds 0 - 9 on the board
    else
        return  false; // position is out of bounds
}

//// Operator overloads
// ostream overload
ostream& operator<< (ostream& out, const Bug* ref_Bug) {
    out << ref_Bug->name <<" (" << ref_Bug->id << ") | Size: " << ref_Bug->size << endl;
    out << "Position: (" << ref_Bug->position.first << ", " << ref_Bug->position.second << ") | Facing: " << directionToString(ref_Bug->direction) << "\n" << endl;

    return out;
}

// greater than ( > ) overload
//bool Bug::operator> (const Bug* other) {
//    if (size > other->size)
//        return true;
//    else
//        return false;
//}


