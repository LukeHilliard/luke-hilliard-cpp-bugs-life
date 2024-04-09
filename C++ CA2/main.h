//
// Created by Luke Hilliard on 29/03/2024.
//
#ifndef C_CA2_BUGSLIFE_H
#define C_CA2_BUGSLIFE_H
#include <iostream>
#include <fstream>
#include <map>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"

using namespace std;
typedef void (*func)();


void displayMenu();
void initializeBugBoard();
void tokenizeInputStream(string, char, vector<Bug*>&);
void displayBoard();
//void displayAddedBugs(const vector<Bug*>&);
#endif //C_CA2_BUGSLIFE_H
