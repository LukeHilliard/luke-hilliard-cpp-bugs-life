#include "main.h"

int main() {
    int choice;
    bool exit = false;
    bool boardIsInitialized;
    Board* board = new Board();
    do{
        boardIsInitialized = board->getBoardState();
        displayMenu();
        cin >> choice;
        switch(choice) {
            case 1: {
                if(!boardIsInitialized) {// if the board is not initialized, initialize it
                    board->initializeBugBoard();
                    break;
                } else { // else prompt for deletion of current bugs
                    char initializeChoice;
                    cout << "WAIT, " << board->getBugAmount() << " bugs have already been added to the board. This action will delete all current bugs\nAre you sure you want to continue?\ny/n : ";
                    cin >> initializeChoice;

                    if(initializeChoice == 'y') {
                        cout << "You can now reinitialize the bug board" << endl;
                        board->updateBoardState(false); // set board state to uninitialized
                    }
                    break;
                }
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

void findBugById() {
    
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









