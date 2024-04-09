//
// Created by Luke Hilliard on 09/04/2024.
//

#ifndef LUKE_HILLIARD_CPP_BUGS_LIFE_BOARD_H
#define LUKE_HILLIARD_CPP_BUGS_LIFE_BOARD_H
#include <vector>
#include <iostream>
using namespace std;

class Board {
private:
    vector<Bug*> bugs;

public:
    // Constructor
    Board() {}

    // Destructor to clean up memory
    ~Board() {
        for (Bug* bug : bugs) {
            delete bug;
        }
    }
};


#endif //LUKE_HILLIARD_CPP_BUGS_LIFE_BOARD_H
