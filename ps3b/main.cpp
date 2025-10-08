// Copyright [2024] <Michael Stanley>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Sokoban.hpp"
 // ********** What needs to get done ***********
    //
    //      -Reset
    //      -MEMORY LEAKS might need destructors
    //      -check if lvl file isopen
    //      -make destructors for structs and maybe tile grid 
    //      - make reset function maybe in << funciton needs to clear
    //
int main(int argc, char* argv[]) {
    // take 1 arguement from command line
    if (argc != 2)
        return 0;

    // get input for level file 
    std::ifstream lvlFile(argv[1]);
    SB::Sokoban Sokban;
    // read lvl file for height, width, and the grid
    lvlFile >> Sokban;
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
    // Make clock 
    sf::Clock c;
    sf::Font alarmClock;
    alarmClock.loadFromFile("alarm clock.ttf");
    // Text box for clock
    sf::Text timeElapsed;
    timeElapsed.setFont(alarmClock);
    timeElapsed.setPosition((Sokban.width()-1.5) * 64, 00);
    timeElapsed.setFillColor(sf::Color(0xFFFFFFFF));
    timeElapsed.setStyle(3);
    timeElapsed.setOutlineColor(sf::Color(0x000000FF));

    // 64 is size of block
    sf::RenderWindow window(sf::VideoMode(Sokban.width() * SB::TILE_SIZE,
         Sokban.height() * SB::TILE_SIZE), "Sokoban!");

    // put level back in output file
    std::ofstream olvlFile("testoutput.lvl", std::ios::out | std::ios::trunc);
     // Check if both files are opened successfully
    
    if (!olvlFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }
    olvlFile << Sokban;
    
    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        Sokban.movePlayer(SB::Direction::Up);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::A:
                        Sokban.movePlayer(SB::Direction::Left);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::S:
                        Sokban.movePlayer(SB::Direction::Down);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::D:
                        Sokban.movePlayer(SB::Direction::Right);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::R:
                        lvlFile >> Sokban;
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    default: 
                        break;
                }
            }
        }
        // Clear the window
        window.clear();
        window.draw(Sokban);

        // Draw clock
        int seconds = c.getElapsedTime().asSeconds();
        int minutes = seconds / 60;
        seconds %= 60;
        // if time less than ten add 0 for spacing
        timeElapsed.setString((minutes < 10 ? "0" : "") +
            std::to_string(minutes)+ ":" +
                (seconds < 10 ? "0" : "") + std::to_string(seconds));
        window.draw(timeElapsed);

        // Display the contents of the window
        window.display();
    }
    return 0;
}
