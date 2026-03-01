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

  queue<Node*> q;
  q.push(execution->graph->start);
  vector<vector<bool>> visited(execution->graph->maze->n,
                               vector<bool>(execution->graph->maze->m, false));

  visited[execution->graph->start->y][execution->graph->start->x] = true;

  while (!q.empty()) {
    Node* node = q.front();
    q.pop();
    matrix[node->y][node->x] = "#";
    for (Node* nn : node->adj) {
      if (visited[nn->y][nn->x]) continue;
      visited[nn->y][nn->x] = true;
      q.push(nn);
    }
  }

  for (int step = 0; step < (*path).size(); step++) {
    Node* node = (*path)[step];
    matrix[node->y][node->x] = "*";
    if (step == (*path).size() - 1 || step == 0) {
      continue;
    }
    Node* nextNode = (*path)[step + 1];

  }

  for (int i = 0; i < execution->graph->maze->n; i++) {
    for (int j = 0; j < execution->graph->maze->m; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  delete[] matrix;
}