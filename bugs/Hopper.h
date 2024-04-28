//
// Created by Luke Hilliard on 17/04/2024.
//

#ifndef CPP_BUGS_LIFE_HOPPER_H
#define CPP_BUGS_LIFE_HOPPER_H
#include "Bug.h"

class Hopper : public Bug{
private:
    int hopLength;

public:
    //// Constructor
    Hopper(int id, string name, int size, bool alive, pair<int, int> position, Direction direction, list<pair<int, int>> path, int hopLength);

    //// Getters
    int getHopLength();

    //// Override derived virtual functions from Bug
    virtual void move(bool) override;
    virtual void updatePath(pair<int, int>&) override;
    virtual void writeLifeHistory(list<pair<int, int>>&) override;
};


#endif //CPP_BUGS_LIFE_HOPPER_H
