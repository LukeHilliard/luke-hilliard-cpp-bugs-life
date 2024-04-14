//
// Created by Luke Hilliard on 14/04/2024.
//

#include "BoardGUI.h"
BoardGUI::BoardGUI() {}
// Sample program main.cpp
void BoardGUI::run() {
        srand(time(NULL));
    // Get the desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Create a window with the same size as the desktop
    sf::RenderWindow window(desktop, "SFML works!", sf::Style::Default);
    if (!window.isOpen()) {
        std::cerr << "Failed to create window. Please check your environment setup." << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


        }

        window.clear();
        // Draw your objects here
        window.display();
    }
}


