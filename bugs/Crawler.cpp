//
// Created by Luke Hilliard on 17/04/2024.
//

#include "Crawler.h"
//// Constructors
Crawler::Crawler(int id, std::string name, int size, bool alive, pair<int, int> position, Direction direction, list<pair<int, int>> path) {
    this->id = id;
    this->name = name;
    this->size = size;
    this->alive = alive;
    this->position = position;
    this->direction = direction;
    this->path = path;
}

/**
 *  Implementation of move functionality for a Crawler. A Crawler can move by 1
 *  in the direction they are facing.
 * Plan:
 *      store position of bug before moving
 *
 *      switch
 *          directions
 *          update next position based on which direction
 *
 *      while is way blocked with next position
 *          reset next position with original position
 *          increase the direction by 1, dont let it go above 4 or below 1
 *          update next position based on which direction
 *
 *          repeat until the way is not blocked with next position
 *
 *      update the position with next position
 *
 *      Making the Bugs move is one of the main reasons I created this repo and started rebuilding my project, I want to try and find the root cause of some of my issues from developing on the shared repo
 */
void Crawler::move(bool changeDirection) {
    pair<int, int> originalPosition = this->position, nextPosition = originalPosition;

    int directionIndex = static_cast<int>(this->direction);
    if(changeDirection) {

        directionIndex++;
        if(directionIndex > 4) // keep index within bounds, 1 - 4
            directionIndex = 1;
        this->direction = static_cast<Direction>(directionIndex);

    }

    switch (this->direction) {
        case Direction::NORTH:
            nextPosition.second -= 1;
            break;
        case Direction::EAST:
            nextPosition.first += 1;
            break;
        case Direction::SOUTH:
            nextPosition.second += 1;
            break;
        case Direction::WEST:
            nextPosition.first -= 1;
            break;
    }

    while(Crawler::isWayBlocked(nextPosition)) {
        //cout << "WAY IS BLOCKED - " << id << " " << name << " " << position.first << ", " << position.second << endl;
        directionIndex++;
        if(directionIndex > 4) // keep index within bounds, 1 - 4
            directionIndex = 1;
        this->direction = static_cast<Direction>(directionIndex);
        //cout << "TRYING " << directionToString(direction) <<endl;
        switch (this->direction) {
            case Direction::NORTH:
                nextPosition.second -= 1;
                break;
            case Direction::EAST:
                nextPosition.first += 1;
                break;
            case Direction::SOUTH:
                nextPosition.second += 1;
                break;
            case Direction::WEST:
                nextPosition.first -= 1;
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
void Crawler::updatePath(pair<int, int> &latestPosition) { this->path.push_back(latestPosition); }
void Crawler::writeLifeHistory() {
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


//string Crawler::toString()  { // TODO change to override >>
//    string status;
//    if(alive)
//        status = "Alive";
//    else
//        status = "Dead";
//    return "| " + this->name + " (" + to_string(id) + ") | " +
//           "Position: (" + to_string(position.first) + ", " + to_string(position.second) + ") | " +
//           "Status: " + status + " | "
//           "Size: " + to_string(size) + " | " +
//           "Facing: " + directionToString(direction) + " \t|\n";
//}
