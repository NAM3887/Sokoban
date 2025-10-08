// Copyright [2024] <Michael Stanley>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    // take 1 arguement from command line
    if (argc != 2)
        return 0;

    // get input for level file
    std::ifstream lvlFile(argv[1]);
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
    SB::Sokoban Sokban;
    // read lvl file for height, width, and the grid
    lvlFile >> Sokban;
    lvlFile.close();
    Sokban.setLvlFilePath(argv[1]);

    // Make clock
    sf::Clock c;
    // Load fonts for text boxes
    sf::Font alarmClock;
    sf::Font openSans;
    alarmClock.loadFromFile("Assets/Fonts/alarm clock.ttf");
    openSans.loadFromFile("Assets/Fonts/OpenSans-Regular.ttf");

    std::string mmSSTimeStr;

    // Text box for clock
    sf::Text timeElapsedText;
    timeElapsedText.setFont(alarmClock);
    timeElapsedText.setPosition((Sokban.width()-1.5) * 64, 00);
    timeElapsedText.setFillColor(sf::Color(0xFFFFFFFF));
    timeElapsedText.setStyle(3);
    timeElapsedText.setOutlineColor(sf::Color(0x000000FF));
    // Text box for win message
    sf::Text winText;
    winText.setFont(openSans);
    winText.setPosition((Sokban.width()/3 +1) * 64,
        (Sokban.height()/2 - 1) * 64);
    winText.setFillColor(sf::Color(0xFFFFFFFF));
    winText.setStyle(3);
    winText.setOutlineColor(sf::Color(0x000000FF));

    sf::SoundBuffer gameWonBuffer;
    if (!gameWonBuffer.loadFromFile("Assets/Sound/mixkit-retro-game-notification-212.wav")) {
        std::cerr << "Failed to load sound file!" << std::endl;
        return 1;
    }
    bool gameWonSoundFlag = false;
    sf::Sound gameWonSound;
    gameWonSound.setBuffer(gameWonBuffer);

    // 64 is size of block
    sf::RenderWindow window(sf::VideoMode(Sokban.width() * SB::TILE_SIZE,
         Sokban.height() * SB::TILE_SIZE), "Sokoban!");

    std::ofstream olvlFile("Levels/testoutput.lvl", std::ios::out | std::ios::trunc);
    // Check if file is opened successfully
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
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                        Sokban.movePlayer(SB::Direction::Up);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::A:
                    case sf::Keyboard::Left:
                        Sokban.movePlayer(SB::Direction::Left);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                        Sokban.movePlayer(SB::Direction::Down);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::D:
                    case sf::Keyboard::Right:
                        Sokban.movePlayer(SB::Direction::Right);
                        olvlFile.seekp(0);
                        olvlFile << Sokban;
                        break;
                    case sf::Keyboard::R:
                        // reset clock
                        c.restart();
                        // reset sound flag
                        gameWonSoundFlag = false;
                        Sokban.reset();
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
        // Draw Game
        window.draw(Sokban);

        if (!Sokban.isWon()) {
            // Draw clock
            mmSSTimeStr = Sokban.getTimeElapsedStr(c);
            timeElapsedText.setString(mmSSTimeStr);
        } else {
            // flag needed to make sure it only plays once per win
            if (!gameWonSoundFlag) {
                gameWonSound.play();
                gameWonSoundFlag = true;
            }
            winText.setString("You Win!\nTime: " + mmSSTimeStr);
            window.draw(winText);
        }

        window.draw(timeElapsedText);
        // Display the contents of the window
        window.display();
    }
    return 0;
}

