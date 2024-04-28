//
// Created by Luke Hilliard on 17/04/2024.
//

#include "Hopper.h"

//// Constructor
Hopper::Hopper(int id, std::string name, int size, bool alive, pair<int, int> position, Direction direction, list<pair<int, int>> path, int hopLength) {
    this->id = id;
    this->name = name;
    this->size = size;
    this->alive = alive;
    this->position = position;
    this->direction = direction;
    this->path = path;
    this->hopLength = hopLength;
}
//// Getters
int Hopper::getHopLength() { return this->hopLength; }

//// Implementation of move functionality for a Hopper. A Crawler can move by its
//// hop length in the direction they are facing.
void Hopper::move(bool changeDirection) {
    pair<int, int> originalPosition = this->position, nextPosition = originalPosition;

    int directionIndex = static_cast<int>(this->direction);
    if(changeDirection) {

        directionIndex++;
        if(directionIndex > 4) // keep index within bounds, 1 - 4
            directionIndex = 1;
        this->direction = static_cast<Direction>(directionIndex);
        cout << "Bug-" << id << " changeDirection= " << directionToString(direction) << endl;
    }

    switch (this->direction) {
        case Direction::NORTH:
            nextPosition.second -= hopLength;
            break;
        case Direction::EAST:
            nextPosition.first += hopLength;
            break;
        case Direction::SOUTH:
            nextPosition.second += hopLength;
            break;
        case Direction::WEST:
            nextPosition.first -= hopLength;
            break;
    }

    while(Hopper::isWayBlocked(nextPosition)) {
        //cout << "WAY IS BLOCKED - " << id << " " << name << " " << position.first << ", " << position.second << endl;
        directionIndex++;
        if(directionIndex > 4) // keep index within bounds, 1 - 4
            directionIndex = 1;
        this->direction = static_cast<Direction>(directionIndex);
        //cout << "TRYING " << directionToString(direction) <<endl;
        switch (this->direction) {
            case Direction::NORTH:
                nextPosition.second -= hopLength;
                break;
            case Direction::EAST:
                nextPosition.first += hopLength;
                break;
            case Direction::SOUTH:
                nextPosition.second += hopLength;
                break;
            case Direction::WEST:
                nextPosition.first -= hopLength;
                break;
        }
        //cout << "MOVING TO " <<  nextPosition.first << ", " << nextPosition.second << endl;
        if(!isWayBlocked(nextPosition)) {
            break;
        } else {
            nextPosition = originalPosition; // reset position
        }
    }
    this->position = nextPosition;
    this->path.push_back(nextPosition);
}


//// Helper methods
void Hopper::updatePath(pair<int, int> &latestPosition) { this->path.push_back(latestPosition); }
void Hopper::writeLifeHistory() {
    string LIFE_HISTORY, status;

    ofstream fout("bugs_life_history_date_time.out", ios::app); // create a file output stream to Output.txt. If the file does not exist create it.
    if(fout) // make sure the file has opened correctly
    {
        // create string to before writing to file
        string positionStr;

        if(alive)
            status = "Alive";
        else
            status = "Dead";

        // construct life history string
        LIFE_HISTORY += this->name + "(" + to_string(this->id) + ") Status: " + status + "\n";
        LIFE_HISTORY += "Final size: " + to_string(this->size) + "\n";
        LIFE_HISTORY += "Moved " + to_string(this->getPathSize()) + " times\n";
        LIFE_HISTORY += "Path: \n";
        // add all paths to line
        for(auto iter = this->path.begin(); iter != this->path.end(); iter++) {
            pair<int, int> nextPosition = *iter; // Dereference iter
            LIFE_HISTORY += "(" + to_string(nextPosition.first) + ", " + to_string(nextPosition.second) + ")";
        }
        LIFE_HISTORY +=  " |";

        // bottom border
        LIFE_HISTORY += "\n";



        fout << LIFE_HISTORY << endl; // add it to the file followed by a new line character.
        fout.close(); // close the file when we are finished.
    } else {
        cout << "Unable to open file." <<endl;
    }
}

