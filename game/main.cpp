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
                while(true) { // Infinite loop until user wants to return to main menu
                    bool isValid = false;
                    if (boardIsInitialized) {
                        int inputId, temp;
                        cout << "Enter an ID to find, -1 to return (e.g. 101): ";
                        cin >> temp;
                        if (temp == -1)
                            break;
                        // stay in loop until input is within normal id range
                        while (temp < 100 || temp > 999) {
                            cout << "--* Bug ID's are 3 digit numbers from 100 - 999 (-1 to exit)*--\n:";
                            cin >> temp;
                            if (temp == -1)
                                break;
                        }
                        if(temp != -1) { // prevent infinite loop when exiting from above while loop
                            inputId = temp; // if this point is reached the ID is valid
                            board->getBugById(inputId);
                        } else {
                            break;
                        }

                    } else {
                        cout << "---* You need to initialise the bug board before you can find one *---" << endl;
                        break;
                    }
                }
                break;
            }
            case 4: {
                board->tapBugBoard();
                break;
            }
            case 5: {
                board->displayAllLifeHistory();
                break;
            }
            case 6: {
                board->displayBoardAsTable();
                break;
            }
            case 7: {

            }
            case 8: {
                board->endGame();
                exit = true;
            }
        }

    } while(!exit);
    return 0;
}

//// Method to display all menu options to the user
void displayMenu() {
    cout << "----------*\tBugs Life\t*----------" << endl;
    cout << "\t  1. Initialise Bug Board\n";
    cout << "\t  2. Display all Bugs\n";
    cout << "\t  3. Find a Bug\n";
    cout << "\t  4. Tap the Bug Board\n";
    cout << "\t  5. Display Life History of all Bugs\n";
    cout << "\t  6. Display all Cells listing their bugs\n";
    cout << "\t  7. Run Simulation\n";
    cout << "\t  8. Exit\n";
}











