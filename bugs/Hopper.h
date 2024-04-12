//
// Created by Luke Hilliard on 08/04/2024.
//
#ifndef C___CA2_HOPPER_H
#define C___CA2_HOPPER_H
#include "Bug.h"
#include "Direction.h"
#include <string>

class Hopper:public Bug {
private:
    int hopLength;

public :
    Hopper(int id, string name, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path, int hopLength);
    Hopper() {}

    virtual void move() override;
    virtual void setPath(pair<int, int>) override;
    virtual void writeLifeHistory(list<pair<int, int>>) override;
    virtual string toString() override;

};


#endif //C___CA2_HOPPER_H
