//
// Created by Luke Hilliard on 08/04/2024.
//

#include "Crawler.h"
#include <fstream>
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
    pair<int, int> nextPosition = this->position; // Create a temporary position before setting the actual position

    // Randomize the length of time a bug stays in a certain direction
    bool doRandomDirection = (rand() % 100 + 1) % 4 == 0; // 25% chance a bug will change direction
    cout << "doRandomDirection on (" << this->id << ") ---> " << doRandomDirection << endl;
    if (doRandomDirection)
        this->direction = getNewDirection(); // Generate a new random direction before moving

    cout << "Moving " << this->name << " (" << this->id << ") from position (" << nextPosition.first << ", " << nextPosition.second << ") to ";

    // Handle the next position based on the direction
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

    // Check if the next position generated is within bounds
    if (!isWayBlocked(nextPosition)) { // If the next position generated is out of bounds
        int badDirectionCount = 0;
        Direction originalDirection = this->direction; // Store the original direction
        bool newPathFound = false;

        do {
            // Try a new direction
            this->direction = getNewDirection();

            // Calculate the next position based on the new direction
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

            // Check if the new path is blocked
            if (isWayBlocked(nextPosition)) {
                newPathFound = true;
                break;
            }

            // Increment bad direction count
            badDirectionCount++;

            // Break if the crawler gets stuck in a loop of bad directions
            if (badDirectionCount > 10000000) {
                newPathFound = true;
                break;
            }
        } while (!newPathFound);

        if (!newPathFound) {
//            cout << " * PATH BLOCKED > 10000000 *" << endl;
//            return;
        }
    }

    // Move the crawler to the new position if the path is not blocked
    cout << "(" << nextPosition.first << ", " << nextPosition.second << ")" << endl;
    position = nextPosition;
    this->path.push_back(position); // Add the next position to the path history
}

//// overloaded move method, takes a position as a parameter and moves bug to that location on the board
void Crawler::move(pair<int, int> nextPosition) {
    this->position = nextPosition;
    this->path.push_back(position); // add next position to path history
}

void Crawler::setPath(pair<int, int>  nextPosition) {
    this->path.push_back(nextPosition);
}

//// Write the life history of an instance of bug to bugs_life_history_date_time.txt
void Crawler::writeLifeHistory(list<pair<int, int>>) {
    string LIFE_HISTORY;

    ofstream fout("bugs_life_history_date_time.out", ios::app); // create a file output stream to Output.txt. If the file does not exist create it.
    if(fout) // make sure the file has opened correctly
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
