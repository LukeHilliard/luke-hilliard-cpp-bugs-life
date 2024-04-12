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
    this->path.push_back(this->position); // before moving add the previous position to history

    pair<int, int> nextPosition = this->position; // create a temporary position before setting actual position
    this->direction = getNewDirection(); // generate a new random direction before moving

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
            this->direction = Crawler::getNewDirection();
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

void Crawler::setPath(pair<int, int>  nextPosition) {
    this->path.push_back(nextPosition);
}

void Crawler::writeNextPositionToFile(list<pair<int, int>>) {
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
    }
    else
    {
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
