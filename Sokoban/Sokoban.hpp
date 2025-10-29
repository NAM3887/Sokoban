// Copyright [2024] <Michael Stanley>
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace SB {

static const size_t TILE_SIZE = 64;

enum Direction { Up, Down, Left, Right };
enum TileType {
    block, crate, ground, storage,
    storageWithCrate, playerDown,
    playerUp, playerLeft, playerRight };

struct Tile {
    // Constructors
    Tile(): tileType(block) {}
    explicit Tile(TileType tt) : tileType(tt), walkable(false) {}

    TileType tileType;
    bool walkable;
    sf::Vector2u gridPosition;
};
// used to store the type of tile the player is on
// and replace it with tiletype of player with direction
// and restores tiletype that got replaced
struct Player {
    Player(): previous(ground), currTile(ground) {}

    TileType previous;
    TileType currTile;
};

// used to store the tiletype the crate is on similar to
// Player but Crate will be used in a vector
// grid position is stored in crate to be able to check if the
// player is next to a crate
struct Crate {
    Crate(): previous(ground), currTile(ground) {}
    explicit Crate(sf::Vector2u gp, TileType starttile) :
        gridPos(gp), currTile(starttile) {}

    sf::Vector2u gridPos;
    TileType previous;
    TileType currTile;
};

class Sokoban : public sf::Drawable {
 public:
    // Constructor
    Sokoban();
    explicit Sokoban(std::string lvlPath);
    // Getters
    const int width() { return _width; }
    const int height() { return _height; }

    // player loc is relative to grid
    const sf::Vector2u playerLoc() { return _playerPosGrid; }
    bool isWon();
    // made for testing crate movement
    TileType getTileTypeAt(sf::Vector2u index)
        { return this->_tiles[index.y][index.x].tileType; };

    // returns elapsed time in mm:ss
    std::string getTimeElapsedStr(const sf::Clock& clock);

    // set file path
    void setLvlFilePath(std::string s) { _lvlFilePath = s; }
    // Move function
    void movePlayer(Direction direction);

    // Extraction and Insertion overload to io to files
    friend std::istream& operator>> (std::istream& is, Sokoban& Sok);
    friend std::ostream& operator<< (std::ostream& os, const Sokoban& Sok);

    // Reset function
    void reset();

 protected:
    // draw function required by sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
    // width and height in tiles
    int _height;
    int  _width;
    bool _gameWon;

    // Textures
    sf::Texture  _blockTexture;
    sf::Texture  _crateTexture;
    sf::Texture  _groundTexture;
    sf::Texture  _storageTexture;
    sf::Texture  _playerDownTexture;
    sf::Texture  _playerUpTexture;
    sf::Texture  _playerLeftTexture;
    sf::Texture  _playerRightTexture;

    // vector 2d of Tile struct
    std::vector<std::vector<Tile>> _tiles;

    // vector of crates used for
    // geting data about crate for moving
    std::vector<Crate> _crates;

    // player data
    sf::Vector2u _playerPosGrid;
    Direction _playerDirection;
    Player _player;

    // level file path
    std::string _lvlFilePath;
};
}  // namespace SB
