#ifndef EXECUTION_H
#define EXECUTION_H

#include <bits/stdc++.h>

#include "./Graph.h"

using namespace std;

struct Position {
  int y;
  int x;

  Position(int y, int x) : y(y), x(x) {}
  Position() {
    y = 0;
    x = 0;
  }
};

struct Execution {
  Graph* graph;

  ~Execution() { delete graph; }
};

#endif