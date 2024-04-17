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
    vector<Bug *> bugs; // vector holding initialized Bugs from txt
    Bug* board[10][10]; // 2D array representing the board, holds pointers to Bug objects
    bool isInitialized;
    int bugsAlive;

public:
    /// Constructor
    Board();

    //// Getters
    bool getBoardState();

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
    void endGame(); // when the game ends manually
    void endGame(Bug*&); // when the game ends via simulation
    void runSimulation();

    /// Display methods
    void displayBoard();
    void displayAllBugs();
    void displayLifeHistory();
    void displayCellsAsList();
};




#endif //CPP_BUGS_LIFE_BOARD_H
