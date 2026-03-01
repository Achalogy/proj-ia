#include <bits/stdc++.h>

#include "../../core/Graph.h"
#include "../../core/Maze.h"
#include "../../core/Node.h"

using namespace std;

pair<int, int> directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

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

void printStep(Maze* maze, map<pair<int, int>, Node*>& nodeCache, int y,
               int x) {
  string** matrix = new string*[maze->n];

  // Dibujamos inicialmente el laberinto sin el camino
  for (int i = 0; i < maze->n; i++) {
    matrix[i] = new string[maze->m];

    for (int j = 0; j < maze->m; j++) {
      string c = "";

      switch (maze->matrix[i][j]) {
        case '0':
          c = ".";
          break;
        case '1':
          c = "|";
          break;
        case '2':
          c = "O";
          break;
        case '3':
          c = "X";
          break;
      }
      matrix[i][j] = c;
    }
  }

  for (auto& [pos, node] : nodeCache) {
    matrix[pos.first][pos.second] = "#";
  }

  matrix[y][x] = "O";

  for (int i = 0; i < maze->n; i++) {
    for (int j = 0; j < maze->m; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

// Dirección
// arriba - 0
// derecha - 1
// abajo - 2
// izquierda - 3
Node* collapseToDirection(Maze* maze, vector<vector<bool>>& visited,
                          map<pair<int, int>, Node*>& nodeCache, Node* curr,
                          int dirIx) {
  pair<int, int> dir = directions[dirIx];
  int y = curr->y + dir.first;
  int x = curr->x + dir.second;
  if (visited[y][x]) return nullptr;

  // printStep(maze, nodeCache, y, x);

  while (validPos(maze, y, x) && maze->matrix[y][x] == '0') {
    if (visited[y][x]) {
      y -= dir.first;
      x -= dir.second;
      break;
    }
    visited[y][x] = true;

    if (getNCount(maze, y, x) > 2) break;

    if (!walkable(maze, y + dir.first, x + dir.second)) {
      // Encontrar siguiente dirección
      int ldirIx = dirIx == 0 ? 3 : dirIx - 1;
      pair<int, int> ldir = directions[ldirIx];
      int rdirIx = dirIx == 3 ? 0 : dirIx + 1;
      pair<int, int> rdir = directions[rdirIx];
      if (walkable(maze, y + ldir.first, x + ldir.second)) {
        dir = ldir;
        dirIx = ldirIx;
      } else if (walkable(maze, y + rdir.first, x + rdir.second)) {
        dir = rdir;
        dirIx = rdirIx;
      }
    }

    y += dir.first;
    x += dir.second;

    // printStep(maze, nodeCache, y, x);
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

  for (int i = 0; i < 4; i++) {
    pair<int, int> direction = directions[i];
    if (walkable(graph->maze, curr->y + direction.first,
                 curr->x + direction.second)) {
      // Guardamos el tamaño del cache antes de colapsar
      size_t cacheSizeBefore = nodeCache.size();

      Node* next =
          collapseToDirection(graph->maze, visited, nodeCache, curr, i);

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