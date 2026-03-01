
#include <bits/stdc++.h>

#include "../../core/Execution.h"
#include "../../core/PathNode.h"

using namespace std;

/*
  Función que ejecuta el algoritmo de busqueda en anchura o BFS sobre un grafo
  dado Retorna el vector de posiciones seguidas para llegar a la salida en orden
*/
vector<Node*>* ExecuteBFS(Execution* execution) {
  if (!execution->graph) {
    return nullptr;
  }

  int n = execution->graph->maze->n;
  int m = execution->graph->maze->m;

  PathNode* start = new PathNode(execution->graph->start, nullptr);
  PathNode* end;

  vector<vector<bool>> visited(n, vector<bool>(m, false));

  queue<PathNode*> q;

  q.push(start);
  visited[start->node->y][start->node->x] = true;

  while (!q.empty()) {
    PathNode* curr = q.front();
    q.pop();

    if (curr->node->type == '3') {
      end = curr;
      break;
    }

    for (pair<int, Node*> u : curr->node->adj) {
      if (visited[u.second->y][u.second->x]) continue;
      visited[u.second->y][u.second->x] = true;

      q.push(new PathNode(u.second, curr));
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