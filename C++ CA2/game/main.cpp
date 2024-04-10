#include "main.h"

int main() {
    map<int, func> menuOptions;

    // TODO add calls to methods for each menu option
    menuOptions[1] = initializeBugBoard;
    menuOptions[2] = displayAllBugs;
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
    cout << "\t  1. Initialise Bug Board\n";
    cout << "\t  2. Display all Bugs\n";
    cout << "\t  3. Find a Bug\n";
    cout << "\t  4. Tap the Bug Board\n";
    cout << "\t  5. Display Life History of all Bugs\n";
    cout << "\t  6. Display all Cells listing their bugs\n";
    cout << "\t  7. Run Simulation\n";
    cout << "\t  8. Exit\n";
}

void initializeBugBoard() {
    Board* board = new Board();
    board->initializeBugBoard();
}

void displayAllBugs() {

}







