#include <iostream>
#include <cstdlib>
#include <memory>
#include "LinkedList.h"
#include "TileCodes.h"

LinkedList::LinkedList(){
   head = nullptr;
   length = 0;   
}

LinkedList::~LinkedList(){
}

LinkedList::LinkedList(const LinkedList& other){
   std::shared_ptr<Node> node = other.head;
   while (node != nullptr) {
      addBack(node -> tile);
      node = node -> next;
   }
}

std::shared_ptr<Node> LinkedList::getNode(int i){
   std::shared_ptr<Node> currentNode = head;
   bool foundNode = false;
   int num = 0;
   while (currentNode != NULL && !foundNode) {
      if (num == i) {
         foundNode = true;
      }
      else {
         num++;
         currentNode = currentNode -> next;
      }
   }
   return currentNode;
}

std::shared_ptr<Tile> LinkedList::getTile(int i){
   return getNode(i) -> tile;
}

int LinkedList::getLength(){
   return length;
}

void LinkedList::addFront(std::shared_ptr<Tile> tile){
   std::shared_ptr<Node> newNode(new Node(tile, head));
   head = newNode;
   length++;
}

void LinkedList::addBack(std::shared_ptr<Tile> tile){
   std::shared_ptr<Node> temp = head;
   std::shared_ptr<Node> last(new Node(tile, NULL));
   if (length == 0) {
      head = last;
   } else {
      while (temp -> next != NULL) {
         temp = temp -> next;
      }
         temp -> next = last;
   }    
   length++;
}

void LinkedList::removeTile(std::shared_ptr<Tile> tile){
   std::shared_ptr<Node> currentNode = head;
   std::shared_ptr<Node> previousNode = NULL;
   
   if (currentNode != NULL && currentNode -> tile -> equalsTile(tile)){
      deleteFront();
   } else {
      while (currentNode != NULL && !(currentNode -> tile -> equalsTile(tile))){
         previousNode = currentNode;
         currentNode = currentNode -> next;
      }
      if (currentNode != NULL){
         previousNode -> next = currentNode -> next;
         length--;
      }
   }
}

void LinkedList::replaceTile(std::shared_ptr<Tile> handTile, std::shared_ptr<Tile> newTile){
   std::shared_ptr<Node> currentNode = head;
   bool replacedTile = false;
   int count = 0;
   while ((count < length) && !(replacedTile)){
      if (currentNode->tile->equalsTile(handTile)){
         currentNode->tile->colour = newTile->colour;
         currentNode->tile->shape = newTile->shape;
         replacedTile = true;
      }
      currentNode = currentNode->next;
      count++;
   }
}

void LinkedList::deleteFront(){
   if (length > 0) {
      std::shared_ptr<Node> temp = head;
      head = head -> next;
      length--;
   }
}

void LinkedList::fillBag(){

   char colors[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++){
         addBack(std::shared_ptr<Tile>(new Tile(colors[i], shapes[j])));
         addBack(std::shared_ptr<Tile>(new Tile(colors[i], shapes[j])));
      }
   }
}

void LinkedList::swap(int index1, int index2){

   std::shared_ptr<Tile> temp = getTile(index1);

   std::shared_ptr<Node> first = getNode(index1);
   std::shared_ptr<Node> second = getNode(index2);

   first -> tile = second -> tile;
   second -> tile = temp;

}

void LinkedList::shuffle(){
   srand(time(NULL));
   for (int i = 0; i < length; i++) {
      swap(i, rand() % length);
   }
}

bool LinkedList::compareTile(std::shared_ptr<Tile> tile){
   std::shared_ptr<Node> currentNode = head;
   bool temp = false;
   while (currentNode != NULL){
      if (currentNode -> tile -> equalsTile(tile)){
         temp = true;
      }
      currentNode = currentNode -> next;
   }
   return temp;
}

std::string LinkedList::toString() {
   std::string list;
   for (int i = 0; i < length; i++){
      if (i + 1 == length) {
         list += getTile(i) -> toString();
      } else {
         list += getTile(i) -> toString() + ",";
      }
   }
   return list;
}

void LinkedList::copyList(std::shared_ptr<LinkedList> list) {
   std::shared_ptr<Node> node = list -> head;
   while (node != nullptr) {
      addBack(node -> tile);
      node = node -> next;
   }
}


