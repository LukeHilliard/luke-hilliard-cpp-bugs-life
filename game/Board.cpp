//
// Created by Luke Hilliard on 09/04/2024.
//


#include "Board.h"
Board::Board() {this->isInitialized = false;}

//// Getters
bool Board::getBoardState() {return this->isInitialized;}
int Board::getBugAmount() {return this->bugs.size();}
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
    if(!isInitialized) {// if the passed parameter is false, clear the memory for new bugs
      this->bugs.clear();
    }
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
            for(int x = 0; x < 10; x++) {
                for(int y = 0; y < 10; y++) {
                   this->board[x][y] = nullptr;
                }
            }
            Board::updateBoardState(true); // update board state once file has been fully loaded
        } else {
            cout << "error opening file." << endl;
        }

        placeBugsOnBoard();
        cout << "* " << bugs.size() << " bugs added to the arena *" << endl;
}


/**
 *          Actions
 */
//// Method to place bug onto the board
void Board::placeBugsOnBoard() {
    for(auto iter = this->bugs.begin(); iter != this-> bugs.end(); iter++) {
        Bug* bug = *iter; // dereference bug from iter
        if(bug->isAlive()) {
            int x = bug->getPosition().first;
            int y = bug->getPosition().second;

            if (this->board[x][y] == nullptr) { // Check if the position is not occupied by another bug
                this->board[x][y] = bug; // place pointer to bug on board
            }
        }
    }
}

void Board::updateBoard() {
    this->bugsAlive = 0;
    // clear board the 'board' with nullptr
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            this->board[i][j] = nullptr;
        }
    }
    for(auto iter = this->bugs.begin(); iter != this-> bugs.end(); iter++) {
        Bug* bug = *iter;
        if(bug->isAlive()) {
            this->board[bug->getPosition().first][bug->getPosition().second] = bug;
            this->bugsAlive++;
        }
    }

}
//// Method to remove the bug from board and set the position to nullptr
void::Board::removeBugFromBoard(Bug* &bugToRemove) {
    // Mark the bug as dead
    bugToRemove->setAlive(false);
    // Clear its position on the board
    this->board[bugToRemove->getPosition().first][bugToRemove->getPosition().second] = nullptr;
}

//// Method to simulate a fight between two bugs.
void Board::fight(Bug* &bug1 , Bug* &bug2) {
    bool bug1IsAlive = false, bug2IsAlive = false;
    if(bug1->isAlive() && bug2->isAlive()) {
        cout << bug1->getName() << " (" << bug1->getID() << ")" << " Vs " << bug2->getName() << " (" << bug2->getID()
             << ")" << endl;

        // find out which bug is bigger and increase side accordingly
        if (bug1->getSize() > bug2->getSize()) {
            bug1->increaseSize(bug2->getSize());

        } else if (bug1->getSize() < bug2->getSize()) {
            bug2->increaseSize(bug1->getSize());
        } else { // bugs are the same size, create a random number from 1 to 10, even bug1=winner | odd bug2=winner
            bool decider = (rand() % 10 + 1) % 2 == 0;
            if (decider) { // is even
                bug1->increaseSize(bug2->getSize());
            } else { // is odd
                bug2->increaseSize(bug1->getSize());
            }
        }
        if (!bug1IsAlive) {// if bug1 lost
            removeBugFromBoard(bug1);
            cout << bug2->getName() << " (" << bug2->getID() << ")" << " has won" << endl;
        }

        if (!bug2IsAlive) { // if bug2 lost
            removeBugFromBoard(bug2);
            cout << bug1->getName() << " (" << bug1->getID() << ")" << " has won" << endl;
        }
    }
}

//// Method to simulate tapping the bug board, calls move method implemented in each Bug class
void Board::tapBugBoard() {
/*
 * loop through bugs_vector
 *      move bug
 *
 * loop through board_vector
       if there is a new-bug with same position but different id
 *          fight update the winner &  remove loser
 *
 * placeBugsOnBoard
 */
    updateBoard();
    displayBoard();
    for(auto moveBugs = this->bugs.begin(); moveBugs != this->bugs.end(); moveBugs++) {
        Bug* bug = *moveBugs;
        if(bug->isAlive())
            bug->move();
    }

    for(auto bugsIter = this->bugs.begin(); bugsIter != this->bugs.end(); bugsIter++) {
        Bug* bug1 = *bugsIter;
        Bug* bug2;

        for(int x=0; x < 10; x++) {
            for(int y=0; y < 10; y++) {
                bug2 = this->board[x][y];

                if(bug2 != nullptr) {
                    if(bug1->getID() != bug2->getID()) {
                        if(bug1->getPosition() == bug2->getPosition()) {
                            fight(bug1, bug2);
                        }
                    }
                }
            }
        }
    }
}

//// Method to run simulation
void Board::runSimulation() {
    cout << this->bugsAlive << endl;
    // sleep_for learned from https://cplusplus.com/reference/thread/this_thread/sleep_for/
    while(this->bugsAlive != 1) { // loop until 1 bug remains
        this->tapBugBoard();
        this_thread::sleep_for(chrono::milliseconds (500)); // stop execution on this thread for 1 second
    }
    Bug* &winner = bugs.at(0);
    this->endGame(winner);
}

//// Method to end game and write path history to file ** overloaded method
void Board::endGame(Bug* &winner) {
    for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
        Bug *bug = *iter;
        bug->writeLifeHistory(bug->getPath());
    }
    cout << winner->getName() <<" (" << winner->getID() << ") is the last one standing." << endl;
}
void Board::endGame() {
    for (auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
        Bug *bug = *iter;
        bug->writeLifeHistory(bug->getPath());
    }
}


/**
 *          Display functions
 */
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

//// Method to display the board
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

//// Method to display all cells listing their bugs
void Board::displayBoardAsTable() {
    if(this->getBoardState()) {
        cout << "Position   |    Holding" << endl;
        for(int x = 0; x < 10; x++) {
            for(int y = 0; y < 10; y++) {
                Bug* bug = board[x][y];
                if(bug != nullptr)  // if there is a bug there
                    cout << "\t(" << x << ", " << y << ") | " << bug->getName() << " (" << bug->getID() << ")" << "Size:" << bug->getSize() << endl;
                else
                    cout <<"\t(" << x << ", " << y << ") | empty" << endl;
            }
        }
        displayBoard();
    } else {
        cout << "---* You need to initialise the bug board before you can display the board *---" << endl;
    }
}





//    for(auto iter = this->bugs.begin(); iter != this->bugs.end(); iter++) {
//        Bug *contender = *iter;
//
//        // Store the original position of the contender bug
//        pair<int, int> originalPosition = contender->getPosition();
//
//        // Move the contender bug
//        contender->move();
//
//        // Check if there is another bug at the new position
//        if (board[contender->getPosition().first][contender->getPosition().second] != nullptr) {
//            // Get the bug at the new position
//            Bug *opponent = board[contender->getPosition().first][contender->getPosition().second];
//
//            // Check if both bugs have landed on the same position
//            if (originalPosition == opponent->getPosition()) {
//                cout << "Two bugs have landed on the same position: (" << originalPosition.first << ", "
//                     << originalPosition.second << ")" << endl;
//                // Handle the situation where bugs land on the same position
//                // You can implement your logic here, such as removing one of the bugs or triggering a fight
//                break;
//            }
//        }
//
//        // Update the board with the contender bug's new position
//        board[originalPosition.first][originalPosition.second] = nullptr;
//        board[contender->getPosition().first][contender->getPosition().second] = contender;


