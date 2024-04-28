//
// Created by Luke Hilliard on 17/04/2024.
//

#ifndef CPP_BUGS_LIFE_CRAWLER_H
#define CPP_BUGS_LIFE_CRAWLER_H
#include "Bug.h"
#include <iostream>

class Crawler : public Bug {

public:
    //// Constructor
    // attributes derived from Bug base class
    Crawler(int id, string name, int size, bool alive, pair<int, int> position, Direction direction, list<pair<int, int>> path);

    //// Override derived virtual functions from Bug
    virtual void move(bool) override;
    virtual void updatePath(pair<int, int>&) override;
    virtual void writeLifeHistory() override;
};


#endif //CPP_BUGS_LIFE_CRAWLER_H
