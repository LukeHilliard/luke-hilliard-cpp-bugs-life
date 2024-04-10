//
// Created by Luke Hilliard on 09/04/2024.
//

#include "Board.h"
Board::Board() {

}
//// Method to initialize bugs based on their type
void Board::tokenizeInputStream(std::string line, char type) {
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

            // stoi to convert string to int
            string attribute = line.substr(start, end - start);

            attributes.push_back(attribute);
        } while (end != -1);

        // Handle the last substring after the last delimiter
        string attribute = line.substr(start);
        if (!attribute.empty()) {
            attributes.push_back(attribute);
        }

        id = stoi(attributes[1]);
        position = {stoi(attributes[2]), stoi(attributes[3])};
        direction = static_cast<Direction>(stoi(attributes[4])); // cast int to Direction
        size = stoi(attributes[5]);
        hopLength = stoi(attributes[6]);
        switch (type) {
            case 'C': {
                // create new Crawler object from the heap
                Crawler *crawler = new Crawler(id, position, direction, size, true, path);
                bugs.push_back(crawler);
                cout << "Crawler added to the arena!\n";
                cout << crawler->toString() << endl;
                break;
            }
            case 'H': {
                // create new Hopper object from the heap
                Hopper *hopper = new Hopper(id, position, direction, size, true, path, hopLength);
                bugs.push_back(hopper);
                cout << "Hopper added to the arena!\n";
                cout << hopper->toString() << endl;
                break;
            }
        }
    }

//// Method to read in data from a file, split into different bug types and passed to tokenizer
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
    } else {
        cout << "error opening file." << endl;
    }
    cout << "* " << bugs.size() << " bugs added to the arena *" << endl;
};

void Board::displayAllBugs() {
    cout << "---* Bugs in play *---" << endl;
    for(auto it = this->bugs.begin(); it != this->bugs.end(); it++) {
        // Access the pointer to Bug object
        Bug* bug = *it;
        cout << bug->toString() << endl;
    }
}