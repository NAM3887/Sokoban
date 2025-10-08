// Copyright [2024] <Michael Stanley>
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {

static const size_t TILE_SIZE = 64;
enum Direction { Up, Down, Left, Right };
enum TileType { block, crate, ground, storage, storageWithCrate, playerDown, playerUp, playerLeft, playerRight };

struct Tile {
    // Constructors
    Tile(): tileType(block) {}
    explicit Tile(TileType tt) : tileType(tt), walkable(false) {}
    TileType tileType;
    bool walkable;
    sf::Vector2u gridPosition;
};
// used to store the type of tile the player is on
// and replace it with tiletype of playe with direction
// and restores tiletype that got replaced
struct Player {
    Player(): previous(ground), currTile(ground) {}
    TileType previous;
    TileType currTile;
    Direction curDir;
};
struct Crate {
    // used to store the tile the crate is on and replace it with A 
    Crate(): previous(ground), currTile(ground) {}
    explicit Crate(sf::Vector2u gp, TileType starttile): gridPos(gp), currTile(starttile) {}
    sf::Vector2u gridPos;
    TileType previous;
    TileType currTile;
};


class Sokoban : public sf::Drawable {
 public:
    // Constructor
    Sokoban();

    // Getters
    const int width() { return _width; }
    const int height() { return _height; }
    const sf::Vector2u playerLoc() { return _playerPosGrid; } // relative to grid
    bool isWon(); 

    // Move function
    void movePlayer(Direction direction);

    // Extraction operator overload to read level file
    friend std::istream& operator>> (std::istream& is, Sokoban& Sok);
    friend std::ostream& operator<< (std::ostream& os, const Sokoban& Sok);

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
    
    // player data
    sf::Vector2u _playerPosGrid;
    Direction _playerDirection;
    Player _player;

    // vector of crates used for
    // geting data about crate for moving
    std::vector<Crate> _crates;
    
};
}  // namespace SB
