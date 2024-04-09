//
// Created by Luke Hilliard on 29/03/2024.
//
#ifndef C_CA2_BUGSLIFE_H
#define C_CA2_BUGSLIFE_H
#include "../bugs/Bug.h"
#include "../bugs/Crawler.h"
#include "../bugs/Hopper.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
typedef void (*func)();

void initializeBugBoard();
void displayMenu();
void displayBoard();
//void displayAddedBugs(const vector<Bug*>&);
#endif //C_CA2_BUGSLIFE_H
