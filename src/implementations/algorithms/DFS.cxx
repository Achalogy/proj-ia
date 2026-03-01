#include "DFS.h"

#include <bits/stdc++.h>

#include "../../core/Execution.h"
#include "../../core/PathNode.h"

using namespace std;

/*
  Función principal del dfs, es la función recursiva que es llamada por cada
  nodo.
*/
PathNode* dfsHelper(vector<vector<bool>>& visited, PathNode* curr) {
  visited[curr->node->y][curr->node->x] = true;

  if (curr->node->type == '3') return curr;

  for (Node* u : curr->node->adj) {
    if (visited[u->y][u->x]) continue;

    PathNode* res = dfsHelper(visited, new PathNode(u, curr));

    if (res != nullptr) return res;
  }
  return nullptr;
}

/*
  Función que ejecuta el algoritmo de busqueda en profundidad o DFS sobre un
  grafo dado Retorna el vector de posiciones seguidas para llegar a la salida en
  orden
*/
vector<Node*>* ExecuteDFS(Execution* execution) {
  if (!execution->graph) {
    return nullptr;
  }

  int n = execution->graph->maze->n;
  int m = execution->graph->maze->m;

  // Inicializamos estructuras
  vector<vector<bool>> visited(n, vector<bool>(m, false));

  Graph* g = execution->graph;
  PathNode* start = new PathNode(g->start, nullptr);
  PathNode* end = dfsHelper(visited, start);

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
