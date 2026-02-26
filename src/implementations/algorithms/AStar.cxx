#include <bits/stdc++.h>

#include "../../core/Execution.h"

using namespace std;

long calc_heuristic(Execution* execution, int i, int j) {
  return abs(execution->graph->end->y - i) + abs(execution->graph->end->x - j);
}

vector<Position>* ExecuteAStar(Execution* execution) {
  int n = execution->graph->maze->n;
  int m = execution->graph->maze->m;

  long start_id = execution->graph->start->id;
  long end_id = execution->graph->end->id;

  vector<vector<int>> heuristic(n, vector<int>(m, INFINITY));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (execution->graph->maze->matrix[i][j] == '0')
        heuristic[i][j] =  // Distancia manhattan
            calc_heuristic(execution, i, j);
    }
  }

  priority_queue<pair<long, long>, vector<pair<long, long>>,
                 greater<pair<long, long>>>
      pq;

  vector<vector<long>> weight(n, vector<long>(m, 1e9));

  vector<long> parent(m * n, -1);

  pq.push(make_pair(heuristic[start_id / m][start_id % m], start_id));
  parent[start_id] = -1;
  weight[start_id / m][start_id % m] = 0;

  while (!pq.empty()) {
    pair<long, long> curr = pq.top();
    pq.pop();
    int i = curr.second / m;
    int j = curr.second % m;

    if (curr.second == end_id) break;

    for (long u : execution->graph->adj[curr.second]) {
      int ui = u / m;
      int uj = u % m;

      long n_weigth = weight[i][j] + 1;

      if (weight[ui][uj] <= n_weigth) continue;

      weight[ui][uj] = n_weigth;
      parent[u] = curr.second;

      pq.push(make_pair(weight[ui][uj] + heuristic[ui][uj], u));
    }
  }

  // Reconstruir recorrido

  long curr = execution->graph->end->id;
  vector<Position> path;

  while (curr != -1) {
    Position pos;
    pos.y = curr / m;
    pos.x = curr % m;

    path.push_back(pos);
    curr = parent[curr];
  }

  return new vector<Position>(path.rbegin(), path.rend());
}