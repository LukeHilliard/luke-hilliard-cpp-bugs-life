//
// Created by Luke Hilliard on 17/04/2024.
//

#ifndef CPP_BUGS_LIFE_BOARD_H
#define CPP_BUGS_LIFE_BOARD_H
#include "../Bugs/Bug.h"
#include "../Bugs/Crawler.h"
#include "../Bugs/Hopper.h"
#include "../Bugs/Direction.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

class Board {
private:
    vector<Bug *> bugs; // vector holding initialized bugs from txt
    Bug* board[10][10]; // 2D array representing the board, a list of pointers to Bug objects
    map<pair<int, int>, list<Bug*>> cellsAtTime; // through each iteration the cells will be cleared and populated with positions and bugs in that position
    bool isInitialized;
    int bugsAlive;

public:
    /// Constructor
    Board();

    //// Getters
    bool getBoardState();
    int getBugsAlive();

    //// Setters
    void updateBoardState(bool);

    //// Initialization
    void initializeBoard();
    void tokenizeInputStream(std::string, char);

    //// Actions towards the board
    void getBugById(int);
    void fight(Bug* &, Bug* &);
    void placeBugsOnBoard();
    void tapBoard();
    void endGame();
    void runSimulation();

    /// Display methods
    void displayBoard();
    void displayAllBugs();
    void displayLifeHistory();
    void displayCellsAsList();
};




#endif //CPP_BUGS_LIFE_BOARD_H
