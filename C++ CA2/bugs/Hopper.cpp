//
// Created by Luke Hilliard on 08/04/2024.
//
#include "Hopper.h"
Hopper::Hopper(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path, int hopLength) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
    this->hopLength = hopLength;
}
void Hopper::move() {

}

string Hopper::toString() {
        string status;
        if(alive)
            status = "Alive";
        else
            status = "Dead";
        return "| Hopper (" + to_string(id) + ") | Hop Length: " + to_string(hopLength) + " | " +
                "Position: (" + to_string(position.first) + ", " + to_string(position.second) + ") | " +
                "Status: " + status + " | " +
                "Size  : " + to_string(size) + " | " +
                "Facing: " + directionToString(direction) + " |\n";

}