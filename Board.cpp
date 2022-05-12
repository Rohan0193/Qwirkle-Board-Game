#include "Board.h"
#include "Tile.h"
#include "TileCodes.h"

#include <memory>

Board::Board(){
    for (int i = 0; i < 26; i++){
        std::vector <std::shared_ptr<Tile>> boardRow;
        board.push_back(boardRow);
        for (int j = 0; j < 26; j++){
            board.at(i).push_back(nullptr);
        }
    }
}

Board::~Board(){
    
}

void Board::addTile(int row, int col, std::shared_ptr<Tile> tile){
    board.at(row).at(col) = tile;
    
}

bool Board::validMove(int row, int col, std::shared_ptr<Tile> tile){
    bool isValid = true;
    bool nextToTile = false;

    std::shared_ptr<Tile> nTile = nullptr;
    std::shared_ptr<Tile> sTile = nullptr;
    std::shared_ptr<Tile> eTile = nullptr;
    std::shared_ptr<Tile> wTile = nullptr;

    if (row > 0){
        nTile = board.at(row - 1).at(col);
    }
    if (row < 25){
        sTile = board.at(row + 1).at(col);
    }
    if (col < 25){
        eTile = board.at(row).at(col + 1);
    }
    if (col > 0){
        wTile = board.at(row).at(col - 1);
    }
    
    // Checks if any adjacent tiles are occupied
    nextToTile = (nTile != nullptr || sTile != nullptr || eTile != nullptr || wTile != nullptr);

    if (nextToTile && board.at(row).at(col) == nullptr){

        // Gets 
        char colRule = getRule(row, col, tile, false);
        char rowRule = getRule(row, col, tile, true);

        bool rowCheck = false;
        bool colCheck = false;

        if (rowRule != NORULE){
            rowCheck = checkLine(row, col, tile, rowRule, true);  
            isValid = rowCheck;  
        }
        if (colRule != NORULE){
            colCheck = checkLine(row, col, tile, colRule, false);
            if (isValid && !colCheck){
                isValid = false;
            }
        }
    }
    else {
        isValid = false;
    }

    return isValid;

}   

void Board::printBoardColoured(){
    std::cout << "   ";
    for (int i = 0; i < 26; i++){
        std::cout << i;
        if (i >= 10){
            std::cout << " ";
        }
        else {
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
    std::cout << "  -";
    for (int i = 0; i < 3 * 26; i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    char currentChar = 'A';
    for (int i = 0; i < 26; i++){
        std::cout << currentChar;
        std::cout << " |";
        currentChar++;
        for (int j = 0; j < 26; j++){
            if (board.at(i).at(j) != nullptr){
                Colour colour = board.at(i).at(j).get()->colour;
                std::string textColour = "";
                if (colour == RED){
                    textColour = RED_TXT;
                }

                else if (colour == ORANGE){
                    textColour = ORANGE_TXT;
                }
                
                else if (colour == YELLOW){
                    textColour = YELLOW_TXT;
                }

                else if (colour == GREEN){
                    textColour = GREEN_TXT;
                }

                else if (colour == BLUE){
                    textColour = BLUE_TXT;
                }
                
                else if (colour == PURPLE){
                    textColour = PURPLE_TXT;
                }

                std::cout << ESC << textColour << "m" << board.at(i).at(j).get()->toString() << RESET;
            }
            else {
                std::cout << "  ";
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}

void Board::printBoard(){
    std::cout << "   ";
    for (int i = 0; i < 26; i++){
        std::cout << i;
        if (i >= 10){
            std::cout << " ";
        }
        else {
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
    std::cout << "  -";
    for (int i = 0; i < 3 * 26; i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    char currentChar = 'A';
    for (int i = 0; i < 26; i++){
        std::cout << currentChar;
        std::cout << " |";
        currentChar++;
        for (int j = 0; j < 26; j++){
            if (board.at(i).at(j) != nullptr){
                std::cout << board.at(i).at(j)->toString();
            }
            else {
                std::cout << "  ";
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}

char Board::getRule(int row, int col, std::shared_ptr<Tile> tile ,bool isCol){
    char rule;
    int colourCount = 0;
    int shapeCount = 0;
    Colour colour = 0;
    Shape shape = 0;
    int tileCount = 0;

    std::shared_ptr<Tile> currentTile = nullptr;
    int currentCoor;
    if (isCol){
        currentCoor = col + 1;
    }
    else {
        currentCoor = row + 1;
    }
    if (25 >= currentCoor){
        currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
    }
    // Iterates through the board in the positive direction (South/East)
    while (currentTile != nullptr && (1 > colourCount && 1 > shapeCount) && 25 >= currentCoor){
        // Defines the characteristics that need to be checked
        if (tileCount == 0){
            colour = currentTile->getColour();
            shape = currentTile->getShape();
        }
        // Checks the second tile if it shares a common characteristic
        // and bases the rule on that
        else {
            if (currentTile->getColour() == colour){
                colourCount++;
            }
            if (currentTile->getShape() == shape){
                shapeCount++;
            }
        }
        tileCount++;
        currentCoor++;
        if (25 >= currentCoor){
            currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
        }
    }
    if (isCol){
        currentCoor = col - 1; 
    }
    else {
        currentCoor = row - 1;
    }

    if (currentCoor >=0){
        currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
    }
    // Iterates in the negative direction (North/West)
    while (currentTile != nullptr && (1 > colourCount && 1 > shapeCount)  && currentCoor >= 0){
        if (tileCount == 0){
            colour = currentTile->getColour();
            shape = currentTile->getShape();
        }
        else {
            if (currentTile->getColour() == colour){
                colourCount++;
            }
            if (currentTile->getShape() == shape){
                shapeCount++;
            }
        }        
        tileCount++;
        currentCoor--;
        if (currentCoor >= 0){
            currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
        }
        
    }
    // Defines the rule based on the check
    if (colourCount == 1){
        rule = COLOURRULE;
        //std::cout << "Colour Rule" << std::endl;
    }
    else if (shapeCount == 1){
        rule = SHAPERULE;
        //std::cout << "Shape Rule" << std::endl;
    }
    else if (tileCount == 1){
        rule = ANYRULE;
        //std::cout << "Any R" << std::endl;
    }
    else {
        rule = NORULE;
        //std::cout << "NO" << std::endl;
    }
    return rule;

}

bool Board::checkLine(int row, int col, std::shared_ptr<Tile> tile, char rule, bool isCol){
    std::shared_ptr<Tile> currentTile = nullptr;
    int currentCoor;
    bool check = true;

    if (isCol){
        currentCoor = col + 1;
    }
    else {
        currentCoor = row + 1;
    }
    if (25 >= currentCoor){
        currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
    }
    // Iterates in the positive direction (South/East)
    while (currentTile != nullptr && check && 25 >= currentCoor){
        // Checks the current tile is a duplicate
        if (tile->equalsTile(currentTile)){
            check = false;
        }
        // Checks if the current tile fits the current rule
        if (rule == COLOURRULE){
            if (tile->getColour() != currentTile->getColour()){
                check = false;
            }
        }
        else if (rule == SHAPERULE){
            if (tile->getShape() != currentTile->getShape()){
                check = false;
            }
        }
        // Checks if the current tile fits any characteristic
        else {
            if (tile->getColour() != currentTile->getColour() && tile->getShape() != currentTile->getShape()){
                check = false;
            }
        }
        currentCoor++;
        if (25 >= currentCoor){
            currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
        }
    }
    if (isCol){
        currentCoor = col - 1;
    }
    else {
        currentCoor = row - 1;
    }
    if (currentCoor >=0){
        currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
    }
    // Iterates in the negative direction (North/West)
    while (currentTile != nullptr && check && currentCoor >= 0){
        if (tile->equalsTile(currentTile)){
            check = false;
        }
        if (rule == COLOURRULE){
            if (tile->getColour() != currentTile->getColour()){
                check = false;
            }
        }
        else if (rule == SHAPERULE){
            if (tile->getShape() != currentTile->getShape()){
                check = false;
            }
        }
        else if (rule == ANYRULE) {
            if (tile->getColour() != currentTile->getColour() && tile->getShape() != currentTile->getShape()){
                check = false;
            }
        }
        currentCoor--;
        if (currentCoor >= 0){
            currentTile = updateTile(row, col, currentCoor, currentTile, isCol);
        }
    }

    return check;
}

int Board::calculatePoints(int row, int col) {
    int totalPoints = 0;
    int points = 0;
    bool tileFound = false;

    for (int i = 0; i < 26; i++){
        if (i == row) {
            tileFound = true;
        }
        if (board.at(i).at(col) != nullptr) {
            points++;
        // Check if tile group actually contains the placed tile
        } else if (tileFound) {
            // Bonus 6 points for completing a set of six
            if (points == 6){
                points += 6;
            }
            totalPoints += points;
            points = 0;
            tileFound = false;
        // If tile group doesn't contain placed tile, does not contribute points
        } else {
            points = 0;
        }
    }

    for (int i = 0; i < 26; i++){
        if (i == col) {
            tileFound = true;
        }
        if (board.at(row).at(i) != nullptr) {
            points++;
        // Check if tile group actually contains the placed tile
        } else if (tileFound) {
            // Bonus 6 points for completing a set of six
            if (points == 6){
                points = points+6;
            }
            totalPoints += points;
            points = 0;
            tileFound = false;
        // If tile group doesn't contain placed tile, does not contribute points
        } else {
            points = 0;
        }
    }

    // Account for double scoring of tile if not in an established row/column
    
    if (row != 0 && row != 25 && col != 0 && col != 25) {

        if ((board.at(row).at(col-1) == nullptr) && (board.at(row).at(col+1) == nullptr)) {
            totalPoints--;
        } else if ((board.at(row-1).at(col) == nullptr) && (board.at(row+1).at(col) == nullptr)) {
            totalPoints--;
        }

    } else {

        if (col == 0) {
            if (board.at(row).at(col+1) == nullptr) {
                totalPoints--;
            }
        } else if (col == 25) {
            if (board.at(row).at(col-1) == nullptr) {
                totalPoints--;
            }
        }

        if (row == 0) {
            if (board.at(row+1).at(col) == nullptr) {
                totalPoints--;
            }
        } else if (row == 25) {
            if (board.at(row-1).at(col) == nullptr) {
                totalPoints--;
            }
        }

    }

    return totalPoints;
}

std::shared_ptr<Tile> Board::updateTile(int row, int col, int currentCoor, std::shared_ptr<Tile> currentTile, bool isCol){
    if (isCol){
        currentTile = board.at(row).at(currentCoor);
    }
    else {
        currentTile = board.at(currentCoor).at(col);
    }
    return currentTile;
}