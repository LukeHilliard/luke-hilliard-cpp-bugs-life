//
// Created by Luke Hilliard on 17/04/2024.
//

#ifndef CPP_BUGS_LIFE_BUG_H
#define CPP_BUGS_LIFE_BUG_H
#include <utility>
#include <list>
#include "Direction.h"

//// BASE CLASS
class Bug {
protected:
    // attributes of a bug
    int id;
    std::string name;
    int size;
    bool alive;
    pair<int, int> position;
    Direction direction;
    list<pair<int, int>> path;
public:
    //// Getters
    int getId();
    std::string getName();
    int getSize();
    bool isAlive();
    pair<int, int> getPosition();
    Direction getDirection();
    list<pair<int, int>>& getPath(); // return a reference to the Bugs path, could be a large list towards the end
    int getPathSize();

    //// Setters
    void eat(int);
    void setAlive(bool);

    //// Virtual methods passed from Base class to children
    virtual void move(bool) = 0;
    virtual void updatePath(pair<int, int>&) = 0;
    virtual void writeLifeHistory(list<pair<int, int>>&) = 0;

    //// Helper methods
    bool isWayBlocked(pair<int, int>&);
    //Direction getNewDirection(Direction);

    //// Operator overloads
    friend std::ostream& operator<<(std::ostream&, const Bug* b);
//    bool operator> (Bug* const*& obj);
//    bool operator< (Bug const*& obj);
};



#endif //CPP_BUGS_LIFE_BUG_H
