//
// Created by Luke Hilliard on 29/03/2024.
//
#ifndef C_CA2_BUG_H
#define C_CA2_BUG_H
#include <utility>
#include <list>
using namespace std;

enum Direction {NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4};

class Bug {
protected:
    int id;
    pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int, int>> path;



    virtual void move() = 0;
    bool isWayBlocked();
};
#endif //C_CA2_BUG_H
