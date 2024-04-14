//
// Created by Luke Hilliard on 14/04/2024.
//

#ifndef C__CA2_BOARDGUI_H
#define C__CA2_BOARDGUI_H
#include <SFML/Graphics.hpp>
#include "../game/Board.h"
#include <vector>
#include <iostream>
using namespace std;

class BoardGUI {
private:
    Board board;


public:
    struct ball {
        int x, y;
        int moveXBy = 1;
        int moveYBy = 1;
        int id;
        int cellSize;
        sf::CircleShape shape;

        ball(int i, int cellSize) {
            shape.setRadius(10);
            shape.setFillColor(sf::Color::Blue);
            x = rand() % 8;
            y = rand() % 8;
            id = i;
            this->cellSize = cellSize;
        }

        void move() {
            x += moveXBy;
            y += moveYBy;

            if (x >= 8 || x == 0) {
                moveXBy *= -1;
            }
            if (y >= 8 || y == 0) {
                moveYBy *= -1;
            }
            cout << id << ":" << x << " " << y << endl;
        }

        void draw(sf::RenderWindow &window) {
            shape.setPosition(x * cellSize, y * cellSize);
            window.draw(shape);
        }
    };
    BoardGUI();

    void run();

};


#endif //C__CA2_BOARDGUI_H
