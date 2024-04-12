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
    // getters
    int getID();
    string getName();
    int getSize();
    pair<int, int> getPosition();
    string getPositionString();
    Direction getDirection();
    list<pair<int, int>> getPath();

    virtual void move() = 0;
    virtual string toString() = 0;
    virtual void setPath(pair<int, int> path) = 0;
    virtual void writeLifeHistory(list<pair<int, int>>) = 0;

    bool isWayBlocked(pair<int, int>);
    Direction getNewDirection();
}
#endif //C_CA2_BUG_H
