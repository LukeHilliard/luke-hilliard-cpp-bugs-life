//
// Created by Luke Hilliard on 14/04/2024.
//

#include "BoardGUI.h"
BoardGUI::BoardGUI() {}
// Sample program main.cpp
void BoardGUI::run() {
        srand(time(NULL));
        sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
//    sf::CircleShape shape(10.f);
//    window.setFramerateLimit(40);
//    shape.setPosition(195, 195);
//    shape.setFillColor(sf::Color::Green);
//    int moveXBy = 5;
//    int moveYBy = 5;
//    bool isGreen = true;
        vector<BoardGUI::ball> balls;
        for(int i  = 0; i < 3; i++) {
            balls.push_back(BoardGUI::ball(i, 50));
        }
        int size = 8;
        vector<sf::RectangleShape> board;
        bool blk = true;
        for(int x = 0; x < size; x++)
        {
            for(int y = 0; y < size; y++)
            {
                sf::RectangleShape rect(sf::Vector2f(50,50));
                rect.setPosition(x*50, y*50);
                if(blk)
                {
                    rect.setFillColor(sf::Color::Black);

                }
                else
                {
                    rect.setFillColor(sf::Color::White);
                }
                blk = !blk;
                board.push_back(rect);
            }
            blk = !blk;
        }
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        for(BoardGUI::ball &b: balls) {
                            b.move();
                        }
                    }

                }
                if(event.type == sf::Event::KeyReleased)
                {
                    cout << event.key.code << endl;
                    cout << sf::Keyboard::C << endl;
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        for(BoardGUI::ball &b: balls) {
                            b.move();
                        }
                    }
                }
//            if(event.type == sf::Event::MouseButtonReleased)
//            {
//                if(event.mouseButton.button == sf::Mouse::Left)
//                {
//                    if(isGreen)
//                    {
//                        shape.setFillColor(sf::Color::Red);
//                        isGreen=false;
//                    }
//                    else
//                    {
//                        shape.setFillColor(sf::Color::Green);
//                        isGreen=true;
//                    }
//                }
//            }

            }
//        shape.move(moveXBy, moveYBy);
//        if(shape.getPosition().x >=380 ||shape.getPosition().x <5 )
//        {
//            moveXBy*=-1;
//        }
//        if(shape.getPosition().y >=380 ||shape.getPosition().y <10 )
//        {
//            moveYBy*=-1;
//        }

            window.clear(sf::Color::White);
            for(sf::RectangleShape &rect : board)
            {
                window.draw(rect);
            }

            for(BoardGUI::ball &b: balls) {

                b.draw(window);
            }
            window.display();

}}

