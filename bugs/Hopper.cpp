//
// Created by Luke Hilliard on 08/04/2024.
//
#include "Hopper.h"
Hopper::Hopper(int id, string name, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path, int hopLength) {
    this->id = id;
    this->name = name;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
    this->hopLength = hopLength;
}
void Hopper::move() {
    pair<int, int> nextPosition = this->position; // create a temporary position before setting actual position

    // handle next position based on direction
    if(Hopper::getDirection() == Direction::NORTH) {
        nextPosition.second -= this->hopLength;
    }
    else if(Hopper::getDirection() == Direction::EAST) {
        nextPosition.first += this->hopLength;
    }
    else if(Hopper::getDirection() == Direction::SOUTH) {
        nextPosition.second += this->hopLength;
    }
    else if(Hopper::getDirection() == Direction::WEST) {
        nextPosition.first -= this->hopLength;
    }

    // check if the next position generated is within bounds
    if(!isWayBlocked(nextPosition)) { // if the next position generated is out of bounds
        while(!isWayBlocked(nextPosition)) {
            //cout << "WAY IS BLOCKED\nPOSITION=" << position.first << "," << position.second << endl;
            this->direction = static_cast<Direction>(rand() % 4 + 1);

            // handle next position based on direction
            if(Hopper::getDirection() == Direction::NORTH) {
                nextPosition.second -= this->hopLength;
            }
            else if(Hopper::getDirection() == Direction::EAST) {
                nextPosition.first += this->hopLength;
            }
            else if(Hopper::getDirection() == Direction::SOUTH) {
                nextPosition.second += this->hopLength;
            }
            else if(Hopper::getDirection() == Direction::WEST) {
                nextPosition.first -= this->hopLength;
            }
        }
    } else {
        position = nextPosition;
    }

}

string Hopper::toString() {
        string status;
        if(alive)
            status = "Alive";
        else
            status = "Dead";
        return "| " + this->name + " (" + to_string(id) + ") | Hop Length: " + to_string(hopLength) + " | " +
                "Position: (" + to_string(position.first) + ", " + to_string(position.second) + ") | " +
                "Status: " + status + " | " +
                "Size  : " + to_string(size) + " | " +
                "Facing: " + directionToString(direction) + " |\n";

}