#ifndef EXECUTION_H
#define EXECUTION_H

#include <bits/stdc++.h>

#include "./Graph.h"

using namespace std;

struct Execution {
  Graph* graph;

  ~Execution() { delete graph; }
};

#endif