#include "Tile.h"
#include "TileCodes.h"
#include <memory>

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}

Colour Tile::getColour(){
    return colour;
}

Shape Tile::getShape(){
    return shape;
}

bool Tile::equalsTile(std::shared_ptr<Tile> compareTile){
    if ((colour == (compareTile->getColour()) && (shape == compareTile->getShape()))){
        return true;
    }
    return false;
}

std::string Tile::toString(){
    std::string returnString = "";
    returnString += colour;
    returnString += std::to_string(shape);

    return returnString;
}
