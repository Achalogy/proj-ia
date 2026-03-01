#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

using namespace std;

struct Node {
  char type;

  int y;
  int x;

  vector<pair<int, Node*>> adj;
};

#endif