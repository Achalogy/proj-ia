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

  // Marcar la ruta expandida con '*'
  for (auto [y,x] : expandedPath) {
    if (execution->graph->maze->matrix[y][x] == '0') {
      matrix[y][x] = "*";
    }
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