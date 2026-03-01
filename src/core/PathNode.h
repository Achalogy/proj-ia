#ifndef PATHNODE_H
#define PATHNODE_H

#include "Node.h"

using namespace std;

struct PathNode {
  Node* node;
  PathNode* parent = nullptr;

  PathNode(Node* _node, PathNode* _parent) {
    this->node = _node;
    this->parent = _parent;
  }
};

#endif