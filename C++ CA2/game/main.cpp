#include "main.h"

int main() {
    int choice;
    bool exit = false;
    Board* board = new Board();
    do{
        displayMenu();
        cin >> choice;
        switch(choice) {
            case 1: {
                board->initializeBugBoard();
                break;
            }
            case 2: {
                board->displayAllBugs();
                break;
            }
            case 3: {

            }
            case 4: {

            }
            case 5: {

            }
            case 6: {

            }
            case 7: {

            }
            case -1: {
                cout << "\n\nProgram ending..." << endl;
                exit = true;
            }
        }

    } while(!exit);
    return 0;
}

// Method to display all menu options to the user
void displayMenu() {
    cout << "----------*\tBugs Life\t*----------" << endl;
    cout << "\t  1. Initialise Bug Board\n";
    cout << "\t  2. Display all Bugs\n";
    cout << "\t  3. Find a Bug\n";
    cout << "\t  4. Tap the Bug Board\n";
    cout << "\t  5. Display Life History of all Bugs\n";
    cout << "\t  6. Display all Cells listing their bugs\n";
    cout << "\t  7. Run Simulation\n";
    cout << "\t  -1. Exit\n";
}








