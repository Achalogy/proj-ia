#include "DFS.h"

#include <bits/stdc++.h>

#include "../../core/Execution.h"

using namespace std;

/*
  Función principal del dfs, es la función recursiva que es llamada por cada nodo.
*/
bool dfsHelper(int u, int target, Graph* graph, vector<bool>& visited,
               map<int, int>& parent) {
  visited[u] = true;

  if (u == target) return true;

  for (int v : graph->adj[u]) {
    if (!visited[v]) {
      parent[v] = u;
      if (dfsHelper(v, target, graph, visited, parent)) {
        return true;
      }
    }
  }
  return false;
}

/*
  Función que ejecuta el algoritmo de busqueda en profundidad o DFS sobre un grafo dado
  Retorna el vector de posiciones seguidas para llegar a la salida en orden
*/
vector<Position>* ExecuteDFS(Execution* execution) {
  if (!execution->graph) {
    return nullptr;
  }

  Graph* g = execution->graph;
  int startId = g->start->id;
  int endId = g->end->id;

  // Inicializamos estructuras
  vector<bool> visited(g->nodes.size(), false);
  map<int, int> parent;
  vector<Position>* path = new vector<Position>();

  // Reconstruir el camino y retornarlo
  if (dfsHelper(startId, endId, g, visited, parent)) {
    int curr = endId;
    while (curr != startId) {
      path->push_back({g->nodes[curr]->y, g->nodes[curr]->x});
      curr = parent[curr];
    }
    path->push_back({g->nodes[startId]->y, g->nodes[startId]->x});

    reverse(path->begin(), path->end());

    return path;
  } else {
    return nullptr;
  }
}
