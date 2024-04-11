//
// Created by Luke Hilliard on 29/03/2024.
//
#ifndef C_CA2_BUG_H
#define C_CA2_BUG_H
#include "Direction.h"
#include <utility>
#include <list>
using namespace std;

class Bug {
protected:

    int id;
    string name;
    pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int, int>> path;

public:
    virtual void move() = 0;
    bool isWayBlocked(pair<int, int>);
    virtual string toString() = 0;

    // getters
    int getID();
    Direction getDirection();
    string getPosition();
};
#endif //C_CA2_BUG_H
