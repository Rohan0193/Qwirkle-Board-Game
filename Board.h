#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include "Tile.h"

#define COLOURRULE  'C'
#define SHAPERULE   'S'
#define NORULE      'N'
#define ANYRULE     'A'

class Board {
public:
    // Constructor & Deconstructor
    Board();
    ~Board();
    // Adds a tile to the specified position 
    void addTile(int row, int col, std::shared_ptr<Tile> tile);
    // Checks if adding a tile to a position is a valid move
    // A variant of validMove for players on their first tile placement
    bool validMove(int row, int col, std::shared_ptr<Tile> tile);
    // Prints a graphical display of thecurrent board state with all tiles
    void printBoard();
    // Prints a COLOURED graphical display of thecurrent board state with all tiles
    void printBoardColoured();
    // Finds how many points are scored by tile placement
    int calculatePoints(int row, int col);

    
private:
    std::vector <std::vector <std::shared_ptr<Tile>>> board;

    // Checks if there is a valid line
    char getRule(int row, int col, std::shared_ptr<Tile> tile ,bool isCol);
    // Check if line with placed tile is valid
    bool checkLine(int row, int col, std::shared_ptr<Tile> tile, char rule ,bool isCol);
    std::shared_ptr<Tile> updateTile(int row, int col, int currentCoor ,std::shared_ptr<Tile> currentTile, bool isCol);

};

#endif