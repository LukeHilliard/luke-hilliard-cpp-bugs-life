//
// Created by Luke Hilliard on 09/04/2024.
//

#include "Board.h"
Board::Board() {
    this->isInitialized = false;
}
//// Getters
bool Board::getBoardState() {return this->isInitialized;}
int Board::getBugAmount() {
    return this->bugs.size();
}
void Board::getBugById(int inputId) {
    bool bugFound = false;
    for(auto it = this->bugs.begin(); it != this->bugs.end(); it++) {
        // Access the pointer to Bug object
        Bug* bug = *it;
        if(bug->getID() == inputId) {
            cout << bug->toString();
            bugFound = true;
        }
    }
    if(!bugFound) {
        cout << "Bug " << inputId << " was not found." << endl;
    }

}

//// Setters
void Board::updateBoardState(bool isInitialized) {
    if(isInitialized == false) // if the passed parameter is false, clear the bugs vector for new bugs
        Board::bugs.clear();
    //TODO  clear memory

    this->isInitialized = isInitialized;
}


//// Method to initialize bugs based on their type
//// Splitting strings inspired from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/ - Method 2: Using C++ find() and substr() APIs.
void Board::tokenizeInputStream(std::string line, char type) {
    bool flagPositionOutOfBounds = false;
    string delimiter = ";";
    vector<string> attributes; // to hold values about bugs
    int start; // start of line
    int end = -1 * delimiter.size();
    int id, size, hopLength;
    Direction direction;
    pair<int, int> position;
    list<pair<int, int> > path;
    do {
        // move the start point to the character immediately after the previous delimiter
        start = end + delimiter.size();
        // find the position of the next delimiter in the string, starting the search from 'start'
        end = line.find(delimiter, start);
        // If the delimiter is not found, substr extracts until the end of the string

        string attribute = line.substr(start, end - start);

        attributes.push_back(attribute);
    } while (end != -1);

    // Handle the last substring after the last delimiter
    string attribute = line.substr(start);
    if (!attribute.empty()) {
        attributes.push_back(attribute);
    }

    // check if position is within bounds
    position = {stoi(attributes[2]), stoi(attributes[3])};
    if (position.first < 0 || position.first > 10 && position.second < 0 || position.second > 10)
        flagPositionOutOfBounds = true;
    if(flagPositionOutOfBounds)
        cout << "**** Positions out of bounds on Bug " << id << ". | Positions: x-" << position.first << " y-" << position.second << "****" << endl;

    // initialize Bug objects only if position is within bounds
    if(!flagPositionOutOfBounds) {
        id = stoi(attributes[1]);
        direction = static_cast<Direction>(stoi(attributes[4])); // cast int to Direction
        size = stoi(attributes[5]);
        hopLength = stoi(attributes[6]);
        switch (type) {
            case 'C': {
                // create new Crawler object from the heap
                Crawler *crawler = new Crawler(id, "Crawler", position, direction, size, true, path);
                bugs.push_back(crawler);
                cout << "Crawler added to the arena!\n";
                cout << crawler->toString() << endl;
                break;
            }
            case 'H': {
                // create new Hopper object from the heap
                Hopper *hopper = new Hopper(id, "Hopper", position, direction, size, true, path, hopLength);
                bugs.push_back(hopper);
                cout << "Hopper added to the arena!\n";
                cout << hopper->toString() << endl;
                break;
            }
        }
    }
}

//// Method to place bug onto the board
void Board::placeBugsOnBoard() {
    for(auto iter = this->bugs.begin(); iter != this-> bugs.end(); iter++) {
        Bug* bug = *iter; // dereference bug from iter
        int x = bug->getPosition().first;
        int y = bug->getPosition().second;

        if (this->board[x][y] == nullptr) { // Check if the position is not occupied by another bug
            this->board[x][y] = bug; // place pointer to bug on board
        } else {
            cout << "Cannot place Bug " << bug->getID() << " because there is a bug there already." << endl;
        }

    }
}
//// Method to read in data from a file, split into different bug types and passed to tokenizeInputStream
void Board::initializeBugBoard() {
        string line;
        ifstream fin("bugs.txt");
        if (fin) {
            while (!fin.eof()) {
                getline(fin, line);
                char bugType = line[0]; // read the first character to get bug type {C = Crawler, H = Hopper}
                if (bugType == 'C') {
                    tokenizeInputStream(line, bugType);
                } else if (bugType == 'H') {
                    tokenizeInputStream(line, bugType);
                }
            }
            fin.close();

            // initialize the 'board' with nullptr
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                   this->board[i][j] = nullptr;
                }
            }
            Board::updateBoardState(true); // update board state once file has been fully loaded
        } else {
            cout << "error opening file." << endl;
        }
        placeBugsOnBoard();
        cout << "* " << bugs.size() << " bugs added to the arena *" << endl;


};

//// Method to display all bugs. Each bug type implements there own toString from Bug class
void Board::displayAllBugs() {
    if(bugs.size() == 0) { // if there are no bugs in play
        cout << "--* You need to initialize the bug board before you can display bugs *--" << endl;
    } else {
        cout << "------*\tBugs in play\t*------" << endl;
        for(auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
            // Access the pointer to Bug object
            Bug* bug = *iter;
            cout << bug->toString() << endl;
        }
    }
}
void Board::displayBoard() {
    // Print top border
    std::cout << "+------------+" << std::endl;

    // Print rows
    for (int i = 0; i < 10; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 10; ++j) {
            if (board[i][j] != nullptr) {
                if (dynamic_cast<Crawler*>(board[i][j]) != nullptr) {
                    std::cout << "C ";
                } else if (dynamic_cast<Hopper*>(board[i][j]) != nullptr) {
                    std::cout << "H ";
                }
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "|" << std::endl;
    }

    // Print bottom border
    std::cout << "+------------+" << std::endl;
}

//// Method to tap the bug board
void Board::tapBugBoard() {
    for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
        Bug *bug = *iter;
        cout << "(Before move)Bug: "<< bug->getID() << " : was at position " << bug->getPositionString() << "\n";
        bug->move();
        cout << "(After move)Bug: "<< bug->getID() << " : was at position " << bug->getPositionString() << "\n";
    }
}



//// Method to display all bugs life history
void Board::displayAllLifeHistory() {
    cout << "--* Life History *--" << endl;

    for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
        Bug *bug = *iter;
        cout << bug->getName() << "(" << bug->getID() << ") | Path history: ";

        // iterate over the path history of current bug
        list<pair<int, int>> path = bug->getPath();
        for (auto pathIter = path.begin(); pathIter != path.end(); pathIter++) {
            pair<int, int> position = *pathIter;
            cout << "(" << position.first << "," << position.second << ") ";
        }
        cout << endl;
    }
}

//// Method to end game and write path history to file
    void Board::endGame() {
        for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
            Bug *bug = *iter;
            cout << "Writing bug life history..." << endl;
            bug->writeNextPositionToFile(bug->getPath());
        }

    }
