//
// Created by Luke Hilliard on 08/04/2024.
//
#ifndef LUKE_HILLIARD_CPP_BUGS_LIFE_CRAWLER_H
#define LUKE_HILLIARD_CPP_BUGS_LIFE_CRAWLER_H
#include "Bug.h"
#include "Direction.h"
#include <string>

class Crawler : public Bug {

public:
    Crawler(int id, string name, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path);
    Crawler();

    virtual void move() override;
    virtual void move(pair<int, int>) override;
    virtual void setPath(pair<int, int>) override;
    virtual void writeLifeHistory(list<pair<int, int>>) override;
    virtual string toString() override;
};


#endif //LUKE_HILLIARD_CPP_BUGS_LIFE_CRAWLER_H
