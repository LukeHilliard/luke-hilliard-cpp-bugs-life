//
// Created by Luke Hilliard on 09/04/2024.
//

#ifndef LUKE_HILLIARD_CPP_BUGS_LIFE_BOARD_H
#define LUKE_HILLIARD_CPP_BUGS_LIFE_BOARD_H
#include "../bugs/Bug.h"
#include "../bugs/Crawler.h"
#include "../bugs/Hopper.h"
#include "../bugs/Direction.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Board {
private:
    vector<Bug *> bugs;
    Bug* board[10][10]; // 2D array representing the board, holds pointers to Bug objects
    bool isInitialized;

public:
    // Constructor
    Board();

    //getters
    bool getBoardState();
    int getBugAmount();
    void getBugById(int);

    // setters
    void updateBoardState(bool);

    // Actions towards the board
    void tokenizeInputStream(string line, char type);
    void placeBugsOnBoard();
    void initializeBugBoard();
    void tapBugBoard();
    void endGame();

    // Display functions
    void displayAllBugs();
    void displayAllLifeHistory();
    void displayBoard();
    void displayBoardAsTable();




};






#endif //LUKE_HILLIARD_CPP_BUGS_LIFE_BOARD_H
