#include <bits/stdc++.h>
#include "../core/Execution.h"
#include "./ExpandPath.h"

using namespace std;

/*
  Función para imprimir el camino (ahora expandido) que se generó con alguno
  de los algoritmos.
*/
void PrintPath(vector<Node*>* path, Execution* execution) {
  if (path == nullptr || path->empty()) {
    cout << "No se encontró un camino." << endl;
    return;
  }

  // Expandir la ruta macro a una ruta completa
  vector<pair<int,int>> expandedPath = expandPath(path, execution);

  // Crear matriz visual
  string** matrix = new string*[execution->graph->maze->n];

  for (int i = 0; i < execution->graph->maze->n; i++) {
    matrix[i] = new string[execution->graph->maze->m];
    for (int j = 0; j < execution->graph->maze->m; j++) {
      char c = execution->graph->maze->matrix[i][j];
      switch (c) {
        case '0': matrix[i][j] = "·"; break;
        case '1': matrix[i][j] = "■"; break;
        case '2': matrix[i][j] = "O"; break;
        case '3': matrix[i][j] = "X"; break;
        default:  matrix[i][j] = "·"; break;
      }
    }
  }


  for(int i = 0; i < expandedPath.size();i++) {
    pair<int, int> step = expandedPath[i];

    string c = "*";

    if(i < expandedPath.size() - 1 && i > 0) {
      pair<int, int> next_step = expandedPath[i+1];

      if(next_step.first - step.first == 1)
        c = "v";
      if(next_step.first - step.first == -1)
        c = "^";
      if(next_step.second - step.second == 1)
        c = ">";
      if(next_step.second - step.second == -1)
        c = "<";
    }

    matrix[step.first][step.second] = c;
  }

  // Imprimir el resultado
  for (int i = 0; i < execution->graph->maze->n; i++) {
    for (int j = 0; j < execution->graph->maze->m; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  delete[] matrix;
}