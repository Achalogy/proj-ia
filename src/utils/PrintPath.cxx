#include <bits/stdc++.h>

#include "../core/Execution.h"

using namespace std;

void PrintPath(vector<Position>* path, Execution* execution) {
  if (path->empty()) return;

  string** matrix = new string*[execution->graph->maze->n];

  for (int i = 0; i < execution->graph->maze->n; i++) {
    matrix[i] = new string[execution->graph->maze->m];

    for (int j = 0; j < execution->graph->maze->m; j++) {
      string c = "";

      switch (execution->graph->maze->matrix[i][j]) {
        case '0':
          c = "·";
          break;
        case '1':
          c = "■";
          break;
        case '2':
          c = "O";
          break;
        case '3':
          c = "X";
          break;
      }
      matrix[i][j] = c;
    }
  }

  for (Position pos : *path) {
    matrix[pos.y][pos.x] = "*";
  }

  for (int i = 0; i < execution->graph->maze->n; i++) {
    for (int j = 0; j < execution->graph->maze->m; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}