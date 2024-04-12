//
// Created by Luke Hilliard on 08/04/2024.
//
#include "Hopper.h"
#include <fstream>
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
    this->path.push_back(this->position); // before moving add the previous position to history

    pair<int, int> nextPosition = this->position; // create a temporary position before setting actual position
    this->direction = getNewDirection(); // generate a new random direction before moving

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
            this->direction = Hopper::getNewDirection();

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

void Hopper::setPath(pair<int, int>  nextPosition) {
    this->path.push_back(nextPosition);
}
// Write the life history of an instance of bug to bugs_life_history_date_time.txt
void Hopper::writeLifeHistory(list<pair<int, int>> path) {
    string LIFE_HISTORY;

    ofstream fout("bugs_life_history_date_time.out", ios::app); // create a file output stream to Output.txt. If the file does not exist create it.
    if(fout) // make sure the file has opened correctly                     add ios::app to open in append mode
    {
        // create string to before writing to file
        string id = to_string(this->id);
        string positionStr;

        // construct life history string
        LIFE_HISTORY = this->name + "(" + to_string(this->id) + ") | Moved " + to_string(this->path.size()) + " times - History: ";
        // add all paths to line
        for(auto iter = this->path.begin(); iter != this->path.end(); iter++) {
            pair<int, int> nextPosition = *iter; // Dereference iter
            positionStr = "(" + to_string(nextPosition.first) + ", " + to_string(nextPosition.second) + ")";
            LIFE_HISTORY += positionStr;
        }
        LIFE_HISTORY +=  " |";
        fout << LIFE_HISTORY << endl; // add it to the file followed by a new line character.
        fout.close(); // close the file when we are finished.
    } else {
        cout << "Unable to open file." <<endl;
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