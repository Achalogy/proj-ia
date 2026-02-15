#include <bits/stdc++.h>

#include "../../core/Graph.h"
#include "../../core/Maze.h"
#include "../../core/Node.h"

using namespace std;

bool validPos(Maze* maze, int i, int j) {
  if (i < 0 || i >= maze->n) return false;
  if (j < 0 || j >= maze->m) return false;
  return true;
}

void tryAddAdj(Maze* maze, Graph* graph, int i, int j, int di, int dj) {
  if (validPos(maze, i + di, j + dj)) {
    if (maze->matrix[i + di][j + dj] == '1') return;

    graph->adj[j + (i * maze->m)].push_back((j + dj) + ((i + di) * maze->m));
  }
}

Graph* MatrixToGraph(Maze* maze) {
  Graph* graph = new Graph;

  long node_count = maze->m * maze->n;

  graph->maze = maze;
  graph->nodes = vector<Node*>(node_count);
  graph->adj = vector<vector<int>>(node_count);

  for (int i = 0; i < maze->n; i++) {
    for (int j = 0; j < maze->m; j++) {
      Node* node = new Node;

      node->id = j + (i * maze->m);
      node->y = i;
      node->x = j;
      node->type = maze->matrix[i][j];

      graph->nodes[node->id] = node;

      if (node->type == '2') graph->start = node;
      if (node->type == '3') graph->end = node;
      if (node->type == '0' || node->type == '2' || node->type == '3') {
        // Pos Arriba
        tryAddAdj(maze, graph, i, j, -1, 0);
        // Pos Derecha
        tryAddAdj(maze, graph, i, j, 0, 1);
        // Pos Abajo
        tryAddAdj(maze, graph, i, j, 1, 0);
        // Pos Izquierda
        tryAddAdj(maze, graph, i, j, 0, -1);
      }
    }
  }

  return graph;
}