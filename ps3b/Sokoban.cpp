// Copyright [2024] <Michael Stanley>
#include "Sokoban.hpp"

#include <fstream>

namespace SB {

// used to load textures everything else is initialized with >> operator
Sokoban::Sokoban() : _height(0), _width(0), _gameWon(false) , _crates() {
    // load textures
    if (!_blockTexture.loadFromFile("block_06.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_groundTexture.loadFromFile("ground_01.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_storageTexture.loadFromFile("ground_04.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerDownTexture.loadFromFile("player_05.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_crateTexture.loadFromFile("crate_03.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerUpTexture.loadFromFile("player_08.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerLeftTexture.loadFromFile("player_20.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerRightTexture.loadFromFile("player_17.png"))
        std::cerr << "Could not load file" << std::endl;
}
Sokoban::Sokoban(std::string lvlPath) : _gameWon(false) , _crates() {
    // load textures
    if (!_blockTexture.loadFromFile("block_06.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_groundTexture.loadFromFile("ground_01.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_storageTexture.loadFromFile("ground_04.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerDownTexture.loadFromFile("player_05.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_crateTexture.loadFromFile("crate_03.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerUpTexture.loadFromFile("player_08.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerLeftTexture.loadFromFile("player_20.png"))
        std::cerr << "Could not load file" << std::endl;
    if (!_playerRightTexture.loadFromFile("player_17.png"))
        std::cerr << "Could not load file" << std::endl;
    std::ifstream lvlFile(lvlPath);
    lvlFile >> *this;
}
// return true when there are no crates
// only storage with crate
bool Sokoban::isWon() {
    // for each vector in _tiles
    for (const auto& insideVec : this->_tiles) {
        // for tile in insideVec if tileType == crate
        // return iterator to tile with crate
        auto it = std::find_if(insideVec.begin(),
            insideVec.end(), [](const Tile& tile)
            { return tile.tileType == TileType::crate;});

        if (it != insideVec.end()) {
            return false;
        }
    }
    // make player face user after win
    this->_tiles[_playerPosGrid.y][_playerPosGrid.x].tileType = playerDown;
    return true;
}
// Checks if the player can move to the tile
//  if the tile is "walkable" (meaning player can walk to tile)
//  if it is then move if not do nothing
// if there is a crate in the way, check if the crate can move
//  if the crate can move then move the crate and the player
//  if not then do nothing
void Sokoban::movePlayer(Direction direction) {
     if (this->isWon())
        return;
    sf::Vector2u pos = this->playerLoc();
    sf::Vector2u posAfterMove;
    TileType playerTypeWithDir;
    int xOffset = 0;
    int yOffset = 0;
    // initialize x and y offsets and new set the type
    // accounting for the way the player is facing
    switch (direction) {
    case Up:
        yOffset = -1;
        playerTypeWithDir = playerUp;
        break;
    case Left:
        xOffset = -1;
        playerTypeWithDir = playerLeft;
        break;
    case Down:
        playerTypeWithDir = playerDown;
        yOffset = +1;
        break;
    case Right:
        playerTypeWithDir = playerRight;
        xOffset = +1;
        break;
    default:
        break;
    }
    posAfterMove.y = pos.y + yOffset;
    posAfterMove.x = pos.x + xOffset;

    // check if player is within bounds
    if (posAfterMove.x >= unsigned(_width) || posAfterMove.x < 0)
        return;
    if (posAfterMove.y >= unsigned(_height) || posAfterMove.y < 0)
        return;

    // check if tile player is trying to move on is crate
    if (this->_tiles[posAfterMove.y][posAfterMove.x].tileType == crate ||
    this->_tiles[posAfterMove.y][posAfterMove.x].tileType == storageWithCrate) {
        // check if crate is at edge of bounds
        if (posAfterMove.x >= unsigned(_width) ||
        (posAfterMove.x == 0 && xOffset < 0))
            return;
        if (posAfterMove.y + yOffset >= unsigned(_height) ||
        posAfterMove.y + yOffset < 0)
            return;
        if (this->_tiles[posAfterMove.y+yOffset]
            [posAfterMove.x+xOffset].walkable) {
            // get crate at position and move it
            for (auto& c : _crates) {
                if (c.gridPos == posAfterMove) {
                    if (c.gridPos.x + xOffset >= unsigned(_width) ||
                    static_cast<int>(c.gridPos.x) + xOffset < 0
                    || c.gridPos.y + yOffset >= unsigned(_height) ||
                    c.gridPos.y + yOffset < 0)
                        return;
                    c.previous = c.currTile;
                    c.currTile = this->_tiles[posAfterMove.y + yOffset]
                    [posAfterMove.x + xOffset].tileType;
                    // update crate Position in grid after move
                    c.gridPos.y += yOffset;
                    c.gridPos.x += xOffset;
                    // change new tiletype
                    if (this->_tiles[posAfterMove.y + yOffset]
                    [posAfterMove.x + xOffset].tileType == storage)
                    this->_tiles[posAfterMove.y + yOffset]
                    [posAfterMove.x + xOffset].tileType = storageWithCrate;
                    else
                        this->_tiles[posAfterMove.y + yOffset]
                        [posAfterMove.x+xOffset].tileType = crate;
                    // set new tile as not walkable
                    // and prev tile to walkable
                    this->_tiles[posAfterMove.y+yOffset]
                        [posAfterMove.x+xOffset].walkable = false;
                    this->_tiles[posAfterMove.y]
                        [posAfterMove.x].tileType = c.previous;
                    this->_tiles[posAfterMove.y]
                        [posAfterMove.x].walkable = true;
                    break;
                }
            }
        } else { return; }
    }
    if (this->_tiles[posAfterMove.y][posAfterMove.x].walkable) {
            _player.previous = _player.currTile;
            _player.currTile = this->_tiles[posAfterMove.y]
                [posAfterMove.x].tileType;
            // update player Position in grid after move
            _playerPosGrid.y += yOffset;
            _playerPosGrid.x += xOffset;
            // change new tile to player tile
            this->_tiles[posAfterMove.y]
                [posAfterMove.x].tileType = playerTypeWithDir;
            this->_tiles[pos.y][pos.x].tileType = _player.previous;
            this->_tiles[pos.y][pos.x].walkable = true;
     }
}
// draw game
void Sokoban::draw(sf::RenderTarget& target,
    sf::RenderStates states) const {
    for (int y = 0; y < this->_height; y++) {
        for (int x = 0; x < this->_width; x++) {
            sf::Sprite tileSprite;
            sf::Sprite BackgroundSprite;
            // set texture based on tileType
            switch (_tiles[y][x].tileType) {
                case block:
                    tileSprite.setTexture(_blockTexture);
                    break;
                case ground:
                    tileSprite.setTexture(_groundTexture);
                    break;
                case storage:
                    tileSprite.setTexture(_storageTexture);
                    break;
                case crate:
                    tileSprite.setTexture(_crateTexture);
                    break;
                case storageWithCrate:
                    tileSprite.setTexture(_crateTexture);
                    break;
                case playerDown:
                    tileSprite.setTexture(_playerDownTexture);
                    break;
                case playerUp:
                    tileSprite.setTexture(_playerUpTexture);
                    break;
                case playerLeft:
                    tileSprite.setTexture(_playerLeftTexture);
                    break;
                case playerRight:
                    tileSprite.setTexture(_playerRightTexture);
                    break;
                default:
                    break;
            }
            // draw background texture if tile is player
            if (_tiles[y][x].tileType == playerDown ||
                _tiles[y][x].tileType == playerUp ||
                _tiles[y][x].tileType == playerLeft ||
                _tiles[y][x].tileType == playerRight ) {
                if (_player.currTile == storage)
                    BackgroundSprite.setTexture(_storageTexture);
                else
                    BackgroundSprite.setTexture(_groundTexture);
            }
            // draw background texture if tile is crate
            if (_tiles[y][x].tileType == crate)
                BackgroundSprite.setTexture(_groundTexture);
            if  (_tiles[y][x].tileType == storageWithCrate)
                BackgroundSprite.setTexture(_storageTexture);
            BackgroundSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(BackgroundSprite, states);
            tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(tileSprite, states);
        }
    }
}
// Initialize height and width
// and vector of (vector of tiles)
std::istream& operator >> (std::istream& is, Sokoban& Sok) {
    bool isCrate = false;
    // read in height and width
    is >> Sok._height >> Sok._width;
    // resize vector for height and width
    Sok._tiles.resize(Sok._height, std::vector<Tile>(Sok._width));
    for (int y = 0; y < Sok._height; y++) {
        for (int x = 0; x < Sok._width; x++) {
            isCrate = false;
            char t;
            is >> t;
            switch (t) {
                case '#':
                    Sok._tiles[y][x] = Tile(block);
                    break;
                case '.':
                    Sok._tiles[y][x] = Tile(ground);
                    Sok._tiles[y][x].walkable = true;
                    break;
                case 'a':
                    Sok._tiles[y][x] = Tile(storage);
                    Sok._tiles[y][x].walkable = true;
                    break;
                case '@':
                    Sok._tiles[y][x] = Tile(playerDown);
                    Sok._playerPosGrid.x = x;
                    Sok._playerPosGrid.y = y;
                    break;
                case 'A':
                   Sok._tiles[y][x] = Tile(crate);
                   isCrate = true;
                   break;
                case '1':
                   Sok._tiles[y][x] = Tile(storageWithCrate);
                   isCrate = true;
                   break;
                default:
                    // ignore
                    break;
            }
            // give each tile a grid position
            sf::Vector2u g(x, y);
            Sok._tiles[y][x].gridPosition = g;
            // make vector of crates
            if (isCrate) {
                // lambda to return a new crate obj
                auto c = [g](TileType tt) -> Crate { return Crate(g, tt); };
                // check if crate is already on storage
                if (Sok._tiles[g.y][g.x].tileType == storageWithCrate)
                    Sok._crates.push_back(c(storage));
                else
                    Sok._crates.push_back(c(ground));
            }
        }
    }
    return is;
}
// writes contents back to file
std::ostream& operator<<(std::ostream& os, const Sokoban& Sok) {
    os << Sok._height << " " << Sok._width << std::endl;
    for (int y = 0; y < Sok._height; y++) {
        for (int x = 0; x < Sok._width; x++) {
            switch (Sok._tiles[y][x].tileType) {
                case block:
                    os << "#";
                    break;
                case ground:
                    os << ".";
                    break;
                case storage:
                    os << "a";
                    break;
                case playerDown:
                    os << "@";
                    break;
                case playerLeft:
                    os << "@";
                    break;
                case playerRight:
                    os << "@";
                    break;
                case playerUp:
                    os << "@";
                    break;
                case crate:
                    os << "A";
                    break;
                case storageWithCrate:
                    os << "1";
                    break;
                default:
                    // Handle any other cases or ignore
                    break;
            }
        }
        os << std::endl;
    }
    return os;
}

// reset function
void Sokoban::reset() {
    this->_gameWon = false;
    // clear vectors
    std::ifstream levelFile(this->_lvlFilePath);
    this->_tiles.clear();
    this->_crates.clear();
    levelFile >> *this;
    levelFile.close();
}

// returns time in a mm:ss string
std::string Sokoban::getTimeElapsedStr(const sf::Clock& clock) {
    int seconds = clock.getElapsedTime().asSeconds();
    int minutes = seconds / 60;
    seconds %= 60;
    // if time is less than 10 add 0 before digit
    std::string mmSSTimeStr = (minutes < 10 ? "0" : "") +
        std::to_string(minutes) + ":" +
        (seconds < 10 ? "0" : "") + std::to_string(seconds);
    return mmSSTimeStr;
}
}  // namespace SB
