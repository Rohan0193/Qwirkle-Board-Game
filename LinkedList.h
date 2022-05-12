
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"
#include <memory>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   LinkedList(const LinkedList& other);

   std::shared_ptr<Tile> getTile(int i);
   std::shared_ptr<Node> getNode(int i);
   int getLength();

   void addFront(std::shared_ptr<Tile> tile);
   void addBack(std::shared_ptr<Tile> tile);

   void removeTile(std::shared_ptr<Tile> tile);
   void replaceTile(std::shared_ptr<Tile> handTile, std::shared_ptr<Tile> newTile);
   void deleteFront();

   void fillBag();
   void swap(int index1, int index2);
   void shuffle();

   bool compareTile(std::shared_ptr<Tile> tile);

   std::string toString();
   void copyList(std::shared_ptr<LinkedList> list);
    
private:
   std::shared_ptr<Node> head;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
