
#include "Node.h"
#include <memory>

Node::Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next) {
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other) {
   tile = std::shared_ptr<Tile>(new Tile(other.tile->colour, other.tile->shape));
   next = other.next;
}
