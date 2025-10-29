// Copyright [2024] <Michael Stanley>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>

using SB::Sokoban;

// Sokoban Fixture
// used to make a reuseable sokoban obj to test with
struct SokobanFixture {
    SB::Sokoban testSokoban;
    std::ifstream lvlFile;
    SokobanFixture() {
        lvlFile.open("testlevel.lvl");
        lvlFile >> testSokoban;
        if (!lvlFile.is_open())
            std::cerr << "Unable to open file." << std::endl;
        lvlFile.close();
    }
};

BOOST_FIXTURE_TEST_CASE(GameWonTest, SokobanFixture) {
    std::ifstream lvlFile("autowin.lvl");
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
    }

    lvlFile >> testSokoban;
    lvlFile.close();

    // Call the isWon() function
    bool gameWon = testSokoban.isWon();
    // test the the game is won
    BOOST_CHECK_EQUAL(gameWon, true);

    testSokoban.reset();
    lvlFile >> testSokoban;
    lvlFile.close();
    BOOST_CHECK_EQUAL(gameWon, true);
}

// in this test the player does not have anything in their way
// this test is to see if the player type is 'moving' correctly
//  within _tiles in all 4 directions
BOOST_FIXTURE_TEST_CASE(PlayerMoveTest, SokobanFixture) {
    std::ifstream lvlFile("testlevel.lvl");
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
    }

    lvlFile >> testSokoban;
    lvlFile.close();
    sf::Vector2u locBeforeMove = testSokoban.playerLoc();

    // move player up 1 tile
    testSokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y-1, testSokoban.playerLoc().y);

    // move player back to original spot
    testSokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    // move player left 1 tile
    testSokoban.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(locBeforeMove.x-1, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    // move player back to original spot
    testSokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);
}

// in this test the player will be blocked in by a wall on each side
// the goal is for the player to not move
BOOST_FIXTURE_TEST_CASE(PlayerBlockedMoveTest, SokobanFixture) {
    std::ifstream lvlFile("testlevel2.lvl");
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
    }

    lvlFile >> testSokoban;
    lvlFile.close();
    sf::Vector2u locBeforeMove = testSokoban.playerLoc();

    // grid position should not change
    // move player up 1 tile
    testSokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    testSokoban.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    testSokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    testSokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);
}
// in this test the player will be blocked in by a wall on each side
// the goal is for the player to not move
BOOST_FIXTURE_TEST_CASE(PlayerMoveOffScreenTest, SokobanFixture) {
    std::ifstream lvlFile("testlevel5.lvl");
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
    }

    lvlFile >> testSokoban;
    lvlFile.close();

    // grid position should not change
    // move player up 1 tile
    testSokoban.movePlayer(SB::Direction::Up);
    sf::Vector2u locBeforeMove = testSokoban.playerLoc();
    testSokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);
}
/*
// Player tried to push the crate to an unobstructed space
// the goal is for the player and the crate to move in each direction
BOOST_FIXTURE_TEST_CASE(PlayerPushCrateTest, SokobanFixture) {
    std::ifstream lvlFile("testlevel3.lvl");
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
    }

    lvlFile >> testSokoban;
    lvlFile.close();
    sf::Vector2u crateAfterMove = testSokoban.playerLoc();

    // move player up 1 tile
    // crate should be 2 tiles up from original loc
    testSokoban.movePlayer(SB::Direction::Up);
    crateAfterMove.y -= 2;

    BOOST_CHECK_EQUAL(testSokoban.getTileTypeAt(crateAfterMove),
        SB::TileType::crate);

    // move player back to original spot
    testSokoban.movePlayer(SB::Direction::Down);

    // move player down 1 tile
    // crate should be 2 tiles down from original loc
    crateAfterMove = testSokoban.playerLoc();
    testSokoban.movePlayer(SB::Direction::Down);
    crateAfterMove.y +=2;
    BOOST_CHECK_EQUAL(testSokoban.getTileTypeAt(crateAfterMove),
        SB::TileType::crate);

    // move player back to original spot
    testSokoban.movePlayer(SB::Direction::Up);

    // move player left 1 tile
    // crate should be 2 tiles left from original loc
    crateAfterMove = testSokoban.playerLoc();
    testSokoban.movePlayer(SB::Direction::Left);
    crateAfterMove.x -= 2;
    BOOST_CHECK_EQUAL(testSokoban.getTileTypeAt(crateAfterMove),
        SB::TileType::crate);

    // move player back to original spot
    testSokoban.movePlayer(SB::Direction::Right);

    // move player right 1 tile
    // crate should be 2 tiles right from original loc
    crateAfterMove = testSokoban.playerLoc();
    testSokoban.movePlayer(SB::Direction::Right);
    crateAfterMove.x +=2;
    BOOST_CHECK_EQUAL(testSokoban.getTileTypeAt(crateAfterMove),
        SB::TileType::crate);
}*/

// in this test the player will try to push a crate
// but the crate is blocked by another crate
// the goal is for the player and the crate to not move
BOOST_FIXTURE_TEST_CASE(PlayerPushCrateOnCrate, SokobanFixture) {
    std::ifstream lvlFile("testlevel4.lvl");
    if (!lvlFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
    }
    lvlFile >> testSokoban;
    lvlFile.close();
    sf::Vector2u locBeforeMove = testSokoban.playerLoc();

    // grid position should not change
    testSokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    testSokoban.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    testSokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);

    testSokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(locBeforeMove.x, testSokoban.playerLoc().x);
    BOOST_CHECK_EQUAL(locBeforeMove.y, testSokoban.playerLoc().y);
}
