//
// Created by Luke Hilliard on 17/04/2024.
//
#include "Board.h"

//// Constructor
Board::Board() {
    this->isInitialized = false; // When Bugs are added to the board this will be changed to true allowed more menu access for things that require Bugs
    for(int x = 0; x < 10; x++) { // Initialize the board with nullptrs
        for(int y = 0; y < 10; y++) {
            this->board[x][y] = nullptr;
        }
    }
}

//// Getters
bool Board::getBoardState() { return this->isInitialized; }
int Board::getBugsAlive() {
    int alive = 0;
    for (auto bugs = this->bugs.begin(); bugs != this->bugs.end(); bugs++) {
        Bug *b = *bugs;
        if (b->isAlive())
            alive++;
    }
    return alive;
}

//// Setters
void Board::updateBoardState(bool state) { this->isInitialized = state; }


//////////////////////////       Initialization         //////////////////////////
//Splitting strings inspired from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/ - Method 2: Using C++ find() and substr() APIs.
void Board::tokenizeInputStream(string line, char type) {
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
    id = stoi(attributes[1]);
    if (position.first >= 0 && position.first < 10 && position.second >= 0 && position.second < 10) {
        // initialize Bug objects only if position is within bounds
        direction = static_cast<Direction>(stoi(attributes[4])); // cast int to Direction
        size = stoi(attributes[5]);
        hopLength = stoi(attributes[6]);
        switch (type) {
            case 'C': {
                // create new Crawler object from the heap
                Crawler* crawler = new Crawler(id, "Crawler", size, true, position, direction, path);
                bugs.push_back(crawler);
                cout << "Crawler added to the arena!\n";
                cout << crawler;
                break;
            }
            case 'H': {
                // create new Hopper object from the heap
                Hopper *hopper = new Hopper(id, "Hopper", size, true, position, direction, path, hopLength);
                bugs.push_back(hopper);
                cout << "Hopper added to the arena!\n";
                cout << hopper;
                break;
            }
        }
    } else {
        cout << "**** Positions out of bounds on Bug " << id << ". | Positions: x-" << position.first << " y-" << position.second << "****" << endl;
    }
}
void Board::initializeBoard() {
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

        placeBugsOnBoard();
        Board::updateBoardState(true); // update board state once file has been fully loaded
    } else {
        cout << "error opening file." << endl;
    }
    cout << "* " << bugs.size() << " bugs added to the arena *" << endl;
}


//////////////////////////       Actions towards the board         //////////////////////////
// Takes an id as a parameter, loops through the bugs vector, if a matching ID is found, display the bug
void Board::getBugById(int id) {
    bool isFound = false;
    for(auto bugsIter = bugs.begin(); bugsIter != bugs.end(); bugsIter++) {
        Bug* b = *bugsIter;
        if(b->getId() == id) {
            isFound = true;
            cout << b << endl; // operator overload
        }
    }
    if(!isFound)
        cout << "No bug with ID " << id << " is currently on the board." << endl;
}

// Takes two references to two bugs and checks which has the bigger size. The biggest "eats" the other and grows by its size, the loser is removed from the board ( alive = false )
void Board::fight(Bug* &bug1, Bug* &bug2) {
    if(bug1->isAlive() && bug2->isAlive()) {
        cout << bug1->getName() << " (" << bug1->getId() << ")" << " Vs " << bug2->getName() << " (" << bug2->getId()
             << ")" << endl;

        // TODO use overloaded operator to check which is bigger
        // find out which bug is bigger and increase side accordingly
        if (bug1 > bug2) { // operator over load, checks which size is bigger
            bug1->eat(bug2->getSize());
            bug2->setAlive(false);
        } else if (bug2 > bug1) {  // operator over load, checks which size is bigger
            bug2->eat(bug1->getSize());
            bug1->setAlive(false);
        }
        else { // bugs are the same size, create a random number from 1 to 10, even bug1=winner | odd bug2=winner
            bool decider = (rand() % 10 + 1) % 2 == 0;
            if (decider) { // is even
                bug1->eat(bug2->getSize());
                bug2->setAlive(false);
            } else { // is odd
                bug2->eat(bug1->getSize());
                bug1->setAlive(false);
            }
        }
        if (!bug1->isAlive()) {// if bug1 lost
            cout << bug2->getName() << " (" << bug2->getId() << ")" << " has won" << endl;
        } else {
            cout << bug1->getName() << " (" << bug1->getId() << ")" << " has won" << endl;
        }
    }
}

// Loops through the bugs vector, if the bug is alive place the bug on the 2D board[][] at the positions provided from Bug
void Board::placeBugsOnBoard() {
    // place bugs that are alive onto the board
    for(auto bugsIter = bugs.begin(); bugsIter != bugs.end(); bugsIter++) {
        Bug* bug = *bugsIter; // dereference bug from iter
        if(bug->isAlive()) {
            if(board[bug->getPosition().first][bug->getPosition().second] == nullptr) { // if the positions provided by the bug are empty on the board
                board[bug->getPosition().first][bug->getPosition().second] = bug;
                //cout << "positions from bugs: " << bug->getId() << " | " << x << ", " << y << endl;
            }
        }
    }
}

// Simulates the "tapping" of the board, created with the idea of rendering in mind, displays the board, iterates through bugs vector and calls move function on each bug with the
// possibility of changing direction, loop through bugs again and check if any have the same position, if they do make them fight, set all positions to nullptrs, call method to place bugs on board, repeat.
void Board::tapBoard() {
    bool changeDirection;


    // cellsAtTime is a map of positions as keys and bugs as elements
    cellsAtTime.clear(); // clear previous positions
    displayBoard();

    // Iterate through all the bugs that are alive and move them passing a bool which allows them to change direction at random
    for (auto moveBugs = this->bugs.begin(); moveBugs != this->bugs.end(); moveBugs++) {
        Bug *bug = *moveBugs;
        changeDirection = (bug->getPathSize() > 0) && ((1 + rand() % 1000) % 3 == 0);
        if (bug->isAlive()) {
            bug->move(changeDirection);
            cellsAtTime[bug->getPosition()].push_back(bug);// store new bug positions on the board
        }
    }

    // Iterate through cellsAtTime if a keys list length is > 1 then more than 1 bug is on that position, they must fight
    for (auto fightBugs = cellsAtTime.begin(); fightBugs != cellsAtTime.end(); fightBugs++) {
//        pair<int, int> position  = fightBugs->first; // key
//        list<Bug*> bugs = fightBugs->second; // value

        // only loop through positions that have more than 1 bug
        if (fightBugs->second.size() > 1) {

            // iterate through the Bugs List
            for (auto bugs = fightBugs->second.begin(); bugs != fightBugs->second.end(); bugs++) {
                if (fightBugs->second.size() == 2) {
                    cout << "2 bugs hand landed on the same cell" << endl;
                    fight(fightBugs->second.front(), fightBugs->second.back());
                } else { // more than one bug is in the cell
                   int biggestSize = 0;
                    Bug* biggestBugInCell;

                    // look through the list to find the biggest bug
                    for(auto bugsList = fightBugs->second.begin(); bugsList != fightBugs->second.end(); bugsList++) {
                        Bug* b = *bugsList;

                        if(b->getSize() > biggestSize) {
                            biggestSize = b->getSize();
                            biggestBugInCell = b;
                        }
                    }
                    //cout << "Biggest " << biggestBugInCell->getName() << " " << biggestBugInCell->getId() << " Size " << biggestBugInCell->getSize() << endl;
                    for(auto eatLosers = fightBugs->second.begin(); eatLosers != fightBugs->second.end(); eatLosers++) {
                        Bug* loser = *eatLosers;
                        if(loser->getId() != biggestBugInCell->getId())
                            fight(biggestBugInCell, loser);
                    }

                    //cout << "New size " << biggestBugInCell->getSize() << endl;
                }
            }
        }
    }


    // reset the board with nullptrs before updating board with new positions
    for (int x = 0; x <= 9; x++) {
        for (int y = 0; y <= 9; y++) {
            this->board[x][y] = nullptr;
        }
    }
    placeBugsOnBoard();
}

void Board::endGame() /* manual ending */ {
    bool bugsLeft = bugs.size() == 1;
    
    // enter this branch if there is more than 1 bug left, the game was ended manually
    if(!bugsLeft) {
        cout << "\t\t\t--------* Bugs remaining *--------" << endl;
        for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
            Bug *bug = *iter;
            bug->writeLifeHistory(bug->getPath());
            cout << bug;
        }
        // delete bugs
        for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
            Bug *b = *iter;
            //delete b;
        }
    } else { // Enter this branch if the game was end automatically due to one bug remaining
        cout << "\t\t\t--------* Winner *--------" << endl;
        Bug* bug = bugs.at(0);
        cout << bug->getName() << " (" << bug->getId() << ")\n";
        cout << "Final size: " << bug->getSize();
        if(bug->getSize() == 20)
            cout << " (MAX)\n";
        else
            cout << endl;
        cout << "Final position: ( " << bug->getPosition().first << ", " << bug->getPosition().second << ")" <<  "\n";
        cout << "Total moves: " << bug->getPathSize() << endl;



    }
}


void Board::runSimulation() {
    // sleep_for learned from https://cplusplus.com/reference/thread/this_thread/sleep_for/
    do{
        this->tapBoard();
        this_thread::sleep_for(chrono::milliseconds (1000)); // stop execution on this thread for 1 second
    } while(bugsAlive > 1); // loop until 1 bug remains

    // if this point is reached there is 1 bug left alive and the game ends
    displayBoard(); // display the final move

    endGame();
}


//////////////////////////       Display methods         //////////////////////////
// Method to display all bugs. Each bug type implements there own TODO operator<< override
void Board::displayAllBugs() {
    if(!Board::isInitialized) { // if the board is not initialised don't allow display all
        cout << "--* You need to initialize the bug board before you can display bugs *--" << endl;
    } else {
        cout << "------*\t  Bugs in play\t*------" << endl;
        for(auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
            // Access the pointer to Bug object
            Bug* bug = *iter;
            cout <<  bug; // operator overload
        }
        cout << endl;
    }
}
// Method to display the board with all bugs in their position at the time of the method being called
void Board::displayBoard() {
    // Print top border
    cout << "+---------------------+" << endl;

    // Print rows
    for (int i = 0; i < 10; ++i) {
        cout << "| ";
        for (int j = 0; j < 10; ++j) {
            if (board[i][j] != nullptr) {
                Bug* bug = board[i][j];
                if (bug->getName() == "Crawler" && bug->isAlive()) { // if bug is type crawler and it is alive
                    cout << "C ";
                } else if (bug->getName() == "Hopper" && bug->isAlive()) { // if bug is type hopper and it is alive
                    cout << "H ";
                } else {
                    cout << ". ";
                }
            } else {
                cout << ". ";
            }
        }
        cout << "|" << endl;
    }
    // Print bottom border
    cout << "+---------------------+" << endl;
}
//  Displays all the positions a Bug has been too up until the point of method call
void Board::displayLifeHistory() {
    string status;
    cout << "--* Life History *--" << endl;
    for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
        Bug *bug = *iter;
        if(bug->isAlive())
            status = "Alive";
        else
            status = "Dead";
        cout << bug->getName() << "(" << bug->getId() << ") Status: " << status << " | Path history: ";
        // iterate over the path history of current bug
        list<pair<int, int>> path = bug->getPath();
        for (auto pathIter = path.begin(); pathIter != path.end(); pathIter++) {
            pair<int, int> position = *pathIter;
            cout << "(" << position.first << "," << position.second << ") ";
        }
        cout << endl;
    }
}
// Displays a list of all cells positions, if a bug is in a cell, the bugs information is displayed along with it
void Board::displayCellsAsList() {
    if(this->getBoardState()) {
        cout << "Position   |    Holding" << endl;
        for(int x = 0; x < 10; x++) {
            for(int y = 0; y < 10; y++) {
                Bug* bug = board[x][y];
                if(bug != nullptr)  // if there is a bug there
                    cout << "\t(" << x << ", " << y << ") | " << bug->getName() << " (" << bug->getId() << ")" << "Size:" << bug->getSize() << endl;
                else
                    cout <<"\t(" << x << ", " << y << ") | empty" << endl;
            }
        }
        displayBoard();
    } else {
        cout << "---* You need to initialise the bug board before you can display the board *---" << endl;
    }
}