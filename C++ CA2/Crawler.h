//
// Created by Luke Hilliard on 08/04/2024.
//
#ifndef LUKE_HILLIARD_CPP_BUGS_LIFE_CRAWLER_H
#define LUKE_HILLIARD_CPP_BUGS_LIFE_CRAWLER_H
#include "Bug.h"



class Crawler : public  Bug {

public:
    Crawler(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int> > path  ) {
        this->id = id;
        this->position = position;
        this->direction = direction;
        this->size = size;
        this->alive = alive;
        this->path = path;
    }

    Crawler() {}

    virtual void move() override;
};


#endif //LUKE_HILLIARD_CPP_BUGS_LIFE_CRAWLER_H
