//
// Created by Luke Hilliard on 09/04/2024.
//

#ifndef C___CA2_DIRECTION_H
#define C___CA2_DIRECTION_H
#include <iostream>
#include <map>
using namespace std;

enum class Direction {NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4};

// adding inline to tell the compiler that this function can be defined in multiple translation
// units without causing linker errors
inline string directionToString(Direction direction) {
    switch (direction) {
        case Direction::NORTH: // left
            return "NORTH";
        case Direction::EAST: // down
            return "EAST";
        case Direction::SOUTH: // right
            return "SOUTH";
        case Direction::WEST: // up
            return "WEST";
        default:
            return "UNKNOWN";
    }
}

#endif //C___CA2_DIRECTION_H
