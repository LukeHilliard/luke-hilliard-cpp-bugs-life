//
// Created by Luke Hilliard on 08/04/2024.
//

#include "Crawler.h"
Crawler::Crawler(int id, string name, pair<int, int> position, Direction direction, int size, bool alive, list<pair<int, int>> path) {
    this->id = id;
    this->name = name;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
    this->path = path;
}
void Crawler::move() {
    pair<int, int> nextPosition = this->position; // create a temporary position before setting actual position

    // handle next position based on direction
    if(Crawler::getDirection() == Direction::NORTH) {
        nextPosition.second--;
    }
    else if(Crawler::getDirection() == Direction::EAST) {
        nextPosition.first++;
    }
    else if(Crawler::getDirection() == Direction::SOUTH) {
        nextPosition.second++;
    }
    else if(Crawler::getDirection() == Direction::WEST) {
        nextPosition.first--;
    }

    // check if the next position generated is within bounds
    if(!isWayBlocked(nextPosition)) { // if the next position generated is out of bounds
        while(!isWayBlocked(nextPosition)) {
            this->direction = static_cast<Direction>(rand() % 4 + 1);
//            cout << directionToString(direction);

            // handle next position based on direction
            if(Crawler::getDirection() == Direction::NORTH) {
                nextPosition.second--;
            }
            else if(Crawler::getDirection() == Direction::EAST) {
                nextPosition.first++;
            }
            else if(Crawler::getDirection() == Direction::SOUTH) {
                nextPosition.second++;
            }
            else if(Crawler::getDirection() == Direction::WEST) {
                nextPosition.first--;
            }
        }
    } else {
        this->position = nextPosition;
    }
}

string Crawler::toString()  {
    string status;
    if(alive)
        status = "Alive";
    else
        status = "Dead";
    return "| " + this->name + " (" + to_string(id) + ") | " +
           "Position: (" + to_string(position.first) + ", " + to_string(position.second) + ") | " +
           "Status: " + status + " | "
           "Size  : " + to_string(size) + " | " +
           "Facing: " + directionToString(direction) + " |\n";
}
