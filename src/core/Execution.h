#ifndef EXECUTION_H
#define EXECUTION_H

#include <bits/stdc++.h>

#include "./Maze.h"

using namespace std;

struct Position {
  int y;
  int x;
};

struct Execution {
  Maze maze;

  Position start;
  Position end;
};

#endif