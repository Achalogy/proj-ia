#include <bits/stdc++.h>

#include "../../core/Execution.h"
#include "../../core/PathNode.h"

using namespace std;

// Función heuristica, calcula la distancia manhattan hacía la salida
long calc_heuristic(Execution* execution, int i, int j) {
  return abs(execution->graph->end->y - i) + abs(execution->graph->end->x - j);
}

/*
  Función que ejecuta el algoritmo de busqueda A* sobre un grafo dado
  Retorna el vector de posiciones seguidas para llegar a la salida en orden
*/
vector<Node*>* ExecuteAStar(Execution* execution) {
  int n = execution->graph->maze->n;
  int m = execution->graph->maze->m;

  PathNode* start = new PathNode(execution->graph->start, nullptr);
  PathNode* end;

  vector<vector<int>> heuristic(n, vector<int>(m, INFINITY));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (execution->graph->maze->matrix[i][j] == '0')
        heuristic[i][j] =  // Distancia manhattan
            calc_heuristic(execution, i, j);
    }
  }

  priority_queue<pair<long, PathNode*>, vector<pair<long, PathNode*>>,
                 greater<pair<long, PathNode*>>>
      pq;

  vector<vector<long>> weight(n, vector<long>(m, 1e9));

  pq.push(make_pair(heuristic[start->node->y][start->node->x], start));

  weight[start->node->y][start->node->x] = 0;

  while (!pq.empty()) {
    pair<long, PathNode*> curr = pq.top();
    pq.pop();

    if (curr.second->node->type == '3') {
      end = curr.second;
      break;
    }

    for (Node* u : curr.second->node->adj) {
      long n_weigth = weight[curr.second->node->y][curr.second->node->x] +
                      curr.second->node->weight;

      if (weight[u->y][u->x] <= n_weigth) continue;

      weight[u->y][u->x] = n_weigth;
      PathNode* nu = new PathNode(u, curr.second);

      pq.push(make_pair(weight[u->y][u->x] + heuristic[u->y][u->x], nu));
    }
  }
  // Reconstruir recorrido

  PathNode* curr = end;
  vector<Node*>* path = new vector<Node*>();

  while (curr != nullptr) {
    path->push_back(curr->node);
    curr = curr->parent;
  }

  reverse(path->begin(), path->end());

  // Retornar un vector reversado
  return path;
}