#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>

#include "./Maze.h"
#include "./Node.h"

using namespace std;

struct Graph {
  Maze* maze;

  Node* start;
  Node* end;

  vector<Node*> nodes;
  vector<vector<int>> adj;
};

#endif