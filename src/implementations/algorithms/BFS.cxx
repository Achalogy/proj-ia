
#include <bits/stdc++.h>

#include "../../core/Execution.h"

using namespace std;

vector<Position>* ExecuteBFS(Execution* execution) {
  if (!execution->graph) {
    return nullptr;
  }

  vector<bool> visited(execution->graph->maze->m * execution->graph->maze->n,
                       false);
  vector<long> parent(execution->graph->maze->m * execution->graph->maze->n,
                      -1);

  queue<long> q;

  q.push(execution->graph->start->id);
  parent[execution->graph->start->id] = -1;
  visited[execution->graph->start->id] = true;

  while (!q.empty()) {
    long curr = q.front();
    q.pop();

    for (long u : execution->graph->adj[curr]) {
      if (visited[u]) continue;
      visited[u] = true;
      parent[u] = curr;

      q.push(u);
    }
  }

  // Reconstruir recorrido

  long curr = execution->graph->end->id;
  vector<Position> path;

  while (curr != -1) {
    Position pos;
    pos.y = curr / execution->graph->maze->m;
    pos.x = curr % execution->graph->maze->m;

    path.push_back(pos);
    curr = parent[curr];
  }

  return new vector<Position>(path.rbegin(), path.rend());
}