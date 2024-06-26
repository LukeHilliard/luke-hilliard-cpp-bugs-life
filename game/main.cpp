#include "main.h"
using namespace std;


int main() {
    int choice;
    bool exit = false;
    bool boardIsInitialized;
    int bugsAlive;

    Board* board = new Board(); // initialize board


    do{
        boardIsInitialized = board->getBoardState();// update board state
        bugsAlive = board->getBugsAlive(); // update how many bugs are alive
        displayMainMenu();

        cin >> choice; // assuming choice is an integer
        
        switch(choice) {
                // Initialize Bug Board
            case 1: {
                if(!boardIsInitialized) {// if the board is not initialized, initialize it
                    board->initializeBoard();
                    break;
                } else { // else prompt for deletion of current bugs
                    char initializeChoice;
                    cout << "WAIT, " /*<< board->getBugAmount()*/ << " bugs have already been added to the board. This action will delete all current bugs\nAre you sure you want to continue?\ny/n : ";
                    cin >> initializeChoice;

                    if(initializeChoice == 'y') {
                        cout << "You can now reinitialize the bug board" << endl;
                       // board->updateBoardState(false); // set board state to uninitialized
                    } else {

                    }
                    break;
                }
            }
                // Display all Bugs
            case 2: {
                board->displayAllBugs();
                break;
            }

                // Find a Bug by ID
            case 3: {
                while(true) { // Infinite loop until user wants to return to main menu
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

                // Tap the Bug Board
            case 4: {
                board->tapBoard();
                break;
            }
                // Display Life History of all Bugs
            case 5: {
              board->displayLifeHistory();
                break;
            }
                // Display all Cells listing their Bugs
            case 6: {
               board->displayCellsAsList();
                break;
            }
                // Run Simulation
            case 7: {
                board->runSimulation();
                break;
            }
                // End Game
            case 8: {
                addHeaderToFile();
                board->endGame();
                exit = true;
                break;
            }

            default: {
                cout << "* Invalid input, select a corresponding number from the menu *\n" << endl;
                break;
            }
        }
        if(bugsAlive == 1) {
            addHeaderToFile();
            board->endGame();
            exit = true;
        }
    } while(!exit);

    delete board; // Free allocated memory

    return 0;
}

//// Method to display all menu options to the user
    void displayMainMenu() {
        cout << "-----------*   Bugs Life   *-----------" << endl;
       // cout << "\t  9. Test SFML\n";
        cout << "\t  1. Initialise Bug Board\n";
        cout << "\t  2. Display all Bugs\n";
        cout << "\t  3. Find a Bug\n";
        cout << "\t  4. Tap the Bug Board\n";
        cout << "\t  5. Display Life History of all Bugs\n";
        cout << "\t  6. Display all Cells listing their bugs\n";
        cout << "\t  7. Run Simulation\n";
        cout << "\t  8. Exit\n";

}

void addHeaderToFile() {
    ofstream fout("bugs_life_history_date_time.out", ios::app); // create a file output stream to Output.txt. If the file does not exist create it.
    if(fout) {
        // get the time the game ended
        std::time_t timeAtEndGame = std::time(nullptr);
        string time = std::ctime(&timeAtEndGame);
        string header;
        header += "\n\nBugs Life Games, Play on " + time + "\nBugs in game --\n";
        fout << header << endl;
        fout.close();
    }

}
