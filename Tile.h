
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include <memory>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   Tile(Colour colour, Shape shape);

   Colour getColour();
   Shape getShape();
   
   bool equalsTile(std::shared_ptr<Tile> compareTile);
   std::string toString();

};

#endif // ASSIGN2_TILE_H
