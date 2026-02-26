#include <bits/stdc++.h>

#include "../core/Execution.h"

using namespace std;

void PrintPath(vector<Position>* path, int rows, int cols) {
  if (path->empty()) return;

  vector<vector<char>> visual(rows, vector<char>(cols, '.'));

  for (const auto& p : *path) {
    visual[p.y][p.x] = '*';
  }

  cout << "\nVisualizacion del camino (DFS):" << endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << visual[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}