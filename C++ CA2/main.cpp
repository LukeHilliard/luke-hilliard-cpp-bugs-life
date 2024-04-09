#include "main.h"

int main() {
    map<int, func> menuOptions;

    // TODO add calls to methods for each menu option
    menuOptions[1] = initializeBugBoard;
//    menuOptions[2] = ;
//    menuOptions[3] = ;
//    menuOptions[4] = ;
//    menuOptions[5] = ;
//    menuOptions[6] = ;
//    menuOptions[7] = ;
//    menuOptions[8] = ;

    int choice = 0;
    string temp;
    do {
        cout << "+----------* Bugs Life *----------+" << endl;
        // display main menu to user, shows all options they can select from
        displayMenu();

        cout << "Please enter an option from the menu (-1 to end): ";
        cin >> choice;
        getline(cin, temp);
        cout << endl;

        // checks if choice exists as a key in menuOptions, if true call method from that key
        if(menuOptions.count(choice))
        {
            menuOptions[choice]();
        }
        // if program has reached this branch and input is not -1, it must be invalid
        else if(choice!=-1)
        {
            cout << "Invalid input, please select a corresponding number from the menu"<<endl;
        }
        cout << "\n";
    }while(choice!=-1);
    return 0;
}

// Method to display all menu options to the user
void displayMenu() {
    cout << "\t  1. Initialize Bug Board\n";
    cout << "\t  2. Display all Bugs\n";
    cout << "\t  3. Find a Bug\n";
    cout << "\t  4. Tap the Bug Board\n";
    cout << "\t  5. Display Life History of all Bugs\n";
    cout << "\t  6. Display all Cells listing their bugs\n";
    cout << "\t  7. Run Simulation\n";
    cout << "\t  8. Exit\n";
}

// Tokenize line inspired from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
void tokenizeInputStream(string line,  char type,  vector<Bug*>& bugs) {
    string delimiter = ";";
    vector<string> attributes;
    int start, end = -1 * delimiter.size();
    int id, x, y, size, hopLength;
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

    if (type == 'C') {
        Crawler *crawler = new Crawler(id, position, direction, size, true, path);
        bugs.push_back(crawler);
        cout << "Crawler added to the arena!\n"
             << "Bug: Crawler (" << id << ")\n"
             << "Size: " << size << "\n" << endl;

    } else if (type == 'H') {
        Hopper *hopper = new Hopper(id, position, direction, size, true, path, hopLength);
        bugs.push_back(hopper);
        cout << "Hopper added to the arena!\n"
             << "Bug: Hopper (" << id << ")\n"
             << "Size: " << size << "\n"
             << "Hop length: " << hopLength << "\n" <<  endl;
    } else {
        cout << "* Invalid bug *" <<endl;
    }


}


// Method to read in data from a text file to initialize bugs before placing them on the board
void initializeBugBoard() {
    string line;
    ifstream fin("bugs.txt");
    vector<Bug*> bug_vector;
    if(fin)
    {
        while(!fin.eof()) {
            getline(fin, line);
            char bugType = line[0]; // read the first character to get bug type {C = Crawler, H = Hopper}
            if(bugType == 'C') {
                tokenizeInputStream(line, bugType, bug_vector);
            } else if(bugType == 'H') {
                tokenizeInputStream(line, bugType, bug_vector);
            }
        }
        fin.close();
    }
    else
    {
        cout << "error opening file." <<endl;
    }
}




