//
// Created by Luke Hilliard on 08/04/2024.
//
#ifndef C___CA2_HOPPER_H
#define C___CA2_HOPPER_H
#include "Bug.h"



class Hopper:public Bug {
protected:
    int hopLength;
public :
    Hopper(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path, int hopLength) {
        this->id = id;
        this->position = position;
        this->direction = direction;
        this->size = size;
        this->alive = alive;
        this->path = path;
        this->hopLength = hopLength;
    }

    Hopper() {}

    virtual void move() override;

};


#endif //C___CA2_HOPPER_H
