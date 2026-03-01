#include <bits/stdc++.h>
#include "../core/Execution.h"

using namespace std;


static bool walkable(Maze* maze, int y, int x) {
  if (y < 0 || y >= maze->n || x < 0 || x >= maze->m) return false;
  return maze->matrix[y][x] != '1';
}

// Reconstruye todos los pasos intermedios entre los nodos de decisión
vector<pair<int,int>> expandPath(vector<Node*>* macroPath, Execution* execution) {
  Maze* maze = execution->graph->maze;
  vector<pair<int,int>> fullPath;

  if (macroPath == nullptr || macroPath->empty()) return fullPath;

  // recorremos cada par consecutivo de nodos
  for (size_t i = 0; i + 1 < macroPath->size(); i++) {
    Node* curr = (*macroPath)[i];
    Node* next = (*macroPath)[i + 1];

    fullPath.push_back({curr->y, curr->x});

    // BFS pequeño para conectar curr -> next
    queue<pair<int,int>> q;
    map<pair<int,int>, pair<int,int>> parent;
    q.push({curr->y, curr->x});
    parent[{curr->y, curr->x}] = {-1, -1};

    bool found = false;
    while (!q.empty() && !found) {
      auto [y, x] = q.front();
      q.pop();

      // Revisar vecinos
      for (auto [dy, dx] : vector<pair<int,int>>{{-1,0},{1,0},{0,-1},{0,1}}) {
        int ny = y + dy, nx = x + dx;
        if (!walkable(maze, ny, nx)) continue;
        if (parent.count({ny, nx})) continue;
        parent[{ny, nx}] = {y, x};
        if (ny == next->y && nx == next->x) {
          found = true;
          break;
        }
        q.push({ny, nx});
      }
    }

    // reconstruir camino curr → next
    vector<pair<int,int>> seg;
    pair<int,int> p = {next->y, next->x};
    while (p.first != -1) {
      seg.push_back(p);
      p = parent[p];
    }
    reverse(seg.begin(), seg.end());

    // agregar al camino total (sin repetir curr)
    for (size_t j = 1; j < seg.size(); j++)
      fullPath.push_back(seg[j]);
  }

  return fullPath;
}