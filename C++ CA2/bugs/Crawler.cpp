//
// Created by Luke Hilliard on 08/04/2024.
//

#include "Crawler.h"
Crawler::Crawler(int id, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
}
void Crawler::move() {

}

string Crawler::toString()  {
    string status;
    if(alive)
        status = "Alive";
    else
        status = "Dead";
    return "| Crawler (" + to_string(id) + ") | " +
           "Position: (" + to_string(position.first) + ", " + to_string(position.second) + ") | " +
           "Status: " + status + " | "
           "Size  : " + to_string(size) + " | " +
           "Facing: " + directionToString(direction) + " |\n";
}
