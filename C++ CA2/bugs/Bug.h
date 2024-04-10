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
    pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int, int>> path;

public:
    virtual void move() = 0;
    bool isWayBlocked(pair<int, int>);
    Direction getDirection();
    virtual string toString() = 0;
    int getID();
};
#endif //C_CA2_BUG_H
