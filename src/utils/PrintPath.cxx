#include <bits/stdc++.h>

#include "../core/Execution.h"

using namespace std;

/*
  Función para inprimir el camino que se genero con alguno de los otros
  algoritmos.
*/
void PrintPath(vector<Node*>* path, Execution* execution) {
  if (path->empty()) return;

  string** matrix = new string*[execution->graph->maze->n];

  // Dibujamos inicialmente el laberinto sin el camino
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

  // Luego por cada posición de la ruta vamos a revisar hacia donde esta yendo
  for (int step = 0; step < (*path).size(); step++) {
    Node* node = (*path)[step];
    matrix[node->y][node->x] = "*";
    if (step == (*path).size() - 1 || step == 0) {
      continue;
    }
    Node* nextNode = (*path)[step + 1];

    cout << "Next node" << endl;
    cout << "  y = " << nextNode->y << endl;
    cout << "  x = " << nextNode->y << endl;
    cout << "Current node" << endl;
    cout << "  y = " << node->y << endl;
    cout << "  x = " << node->y << endl;

    int dy = nextNode->y - node->y;
    int dx = nextNode->x - node->x;

    if (dy == -1)
      matrix[node->y][node->x] = "^";
    else if (dy == 1)
      matrix[node->y][node->x] = "V";
    else if (dx == 1)
      matrix[node->y][node->x] = ">";
    else if (dx == -1)
      matrix[node->y][node->x] = "<";
  }

  for (int i = 0; i < execution->graph->maze->n; i++) {
    for (int j = 0; j < execution->graph->maze->m; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  delete[] matrix;
}