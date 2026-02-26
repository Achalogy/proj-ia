
#include <bits/stdc++.h>

#include "../../core/Execution.h"

using namespace std;

vector<Position> ExecuteBFS(Execution* execution) {
  cout << "Empezando :D " << execution->graph->maze->m << endl;
  cout << "Empezando :D " << execution->graph->maze->n << endl;
  cout << "Empezando :D " << execution->graph->maze->matrix << endl;
  vector<bool> visited(execution->graph->maze->m * execution->graph->maze->n);
  vector<long> parent(execution->graph->maze->m * execution->graph->maze->n);

  queue<long> q;

  q.push(execution->graph->start->id);
  parent[execution->graph->start->id] = -1;

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
    pos.y = curr / execution->graph->maze->n;
    pos.x = curr % execution->graph->maze->n;

    cout << "y=" << pos.y << " - x=" << pos.x << endl;

    path.push_back(pos);
    curr = parent[curr];
  }

  return vector<Position>(path.rend(), path.rbegin());
}