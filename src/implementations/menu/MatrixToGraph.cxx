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

bool walkable(Maze* maze, int i, int j) {
  return validPos(maze, i, j) && maze->matrix[i][j] != '1';
}

Node* getStartNode(Maze* maze) {
  for (int i = 0; i < maze->n; i++) {
    for (int j = 0; j < maze->m; j++) {
      if (maze->matrix[i][j] == '2') {
        Node* node = new Node();
        node->x = j;
        node->y = i;
        node->adj = vector<Node*>();

        return node;
      }
    }
  }
  return nullptr;
}

int getNCount(Maze* maze, int i, int j) {
  int count = 0;

  // Arriba
  if (walkable(maze, i - 1, j)) count++;
  // Derecha
  if (walkable(maze, i, j + 1)) count++;
  // Abajo
  if (walkable(maze, i + 1, j)) count++;
  // Izquierda
  if (walkable(maze, i, j - 1)) count++;

  return count;
}

// Dirección
// arriba - 0
// derecha - 1
// abajo - 2
// izquierda - 3
Node* collapseToDirection(Maze* maze, vector<vector<bool>>& visited,
                          map<pair<int, int>, Node*>& nodeCache, Node* curr,
                          pair<int, int> dir) {
  int y = curr->y + dir.first;
  int x = curr->x + dir.second;

  while (validPos(maze, y, x) && maze->matrix[y][x] == '0') {
    if (visited[y][x]) {
      return nullptr;
    }
    visited[y][x] = true;

    if (getNCount(maze, y, x) > 2) break;

    y += dir.first;
    x += dir.second;
  }
  if (!walkable(maze, y, x)) {
    y -= dir.first;
    x -= dir.second;
  }

  if (nodeCache.count({y, x})) {
    return nodeCache[{y, x}];
  }

  Node* node = new Node();
  node->adj = vector<Node*>();
  node->type = maze->matrix[y][x];
  node->x = x;
  node->y = y;

  nodeCache[{y, x}] = node;

  return node;
}

Node* buildGraph(Graph* graph, vector<vector<bool>>& visited,
                 map<pair<int, int>, Node*>& nodeCache, Node* curr) {
  if (curr == nullptr) {
    curr = getStartNode(graph->maze);
    nodeCache[{curr->y, curr->x}] = curr;
  }

  if (curr->type == '3') {
    graph->end = curr;
  }

  int dy[] = {-1, 0, 1, 0};
  int dx[] = {0, 1, 0, -1};

  for (int i = 0; i < 4; i++) {
    if (walkable(graph->maze, curr->y + dy[i], curr->x + dx[i])) {
      // Guardamos el tamaño del cache antes de colapsar
      size_t cacheSizeBefore = nodeCache.size();

      Node* next = collapseToDirection(graph->maze, visited, nodeCache, curr,
                                       {dy[i], dx[i]});

      if (next != nullptr) {
        curr->adj.push_back(next);

        // Si el cache creció, significa que 'next' es un nodo NUEVO
        // Si es nuevo, debemos explorarlo. Si no, solo lo conectamos (arriba).
        if (nodeCache.size() > cacheSizeBefore) {
          buildGraph(graph, visited, nodeCache, next);
        }
      }
    }
  }

  return curr;
}

// Función para convertir una matriz a una estructura de grafo usando
// apuntadores.
Graph* MatrixToGraph(Maze* maze) {
  Graph* graph = new Graph();

  graph->start = nullptr;
  graph->end = nullptr;

  long node_count = maze->m * maze->n;

  vector<vector<bool>> visited(maze->n, vector<bool>(maze->m, false));
  map<pair<int, int>, Node*> nodeCache;

  graph->maze = maze;
  graph->start = buildGraph(graph, visited, nodeCache, nullptr);

  if (graph->start == nullptr) {
    cout << "El laberinto no tiene inicio" << endl;
    delete graph;
    return nullptr;
  }
  if (graph->end == nullptr) {
    cout << "El laberinto no tiene salida" << endl;
    delete graph;
    return nullptr;
  }

  cout << "Laberinto válido, grafo generado" << endl;

  return graph;
}