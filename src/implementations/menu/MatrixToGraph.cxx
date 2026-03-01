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
// Función para convertir una matriz a una estructura de grafo usando
// apuntadores.

void getAdj(Maze* maze, vector<vector<Node*>> nodeMatrix, Node* curr,
            vector<vector<bool>>& visited, int i, int j, int w) {
  if (visited[i][j]) return;
  visited[i][j] = true;

  if (!(i == curr->y && j == curr->x)) {
    if (nodeMatrix[i][j] != nullptr) {
      // cout << "Adj desde " << endl;
      // cout << " x: " << curr->x << endl;
      // cout << " y: " << curr->y << endl;
      // cout << "Hasta" << endl;
      // cout << " x: " << nodeMatrix[i][j]->x << endl;
      // cout << " y: " << nodeMatrix[i][j]->y << endl;
      // cout << "Con peso " << w << endl;
      // cout << endl;
      curr->adj.push_back({w, nodeMatrix[i][j]});
      return;
    }
  }

  // Arriba
  if (walkable(maze, i - 1, j))
    getAdj(maze, nodeMatrix, curr, visited, i - 1, j, w + 1);
  // Derecha
  if (walkable(maze, i, j + 1))
    getAdj(maze, nodeMatrix, curr, visited, i, j + 1, w + 1);
  // Abajo
  if (walkable(maze, i + 1, j))
    getAdj(maze, nodeMatrix, curr, visited, i + 1, j, w + 1);
  // Izquierda
  if (walkable(maze, i, j - 1))
    getAdj(maze, nodeMatrix, curr, visited, i, j - 1, w + 1);
}

Graph* MatrixToGraph(Maze* maze) {
  Graph* graph = new Graph();

  graph->maze = maze;

  vector<Node*> nodes;
  vector<vector<Node*>> nodeMatrix(maze->n, vector<Node*>(maze->m, nullptr));

  for (int i = 0; i < maze->n; i++) {
    for (int j = 0; j < maze->m; j++) {
      Node* node = nullptr;
      switch (maze->matrix[i][j]) {
        case '0': {
          int adjCount = getNCount(maze, i, j);
          if (adjCount != 2) {
            node = new Node();
          }
          break;
        }
        case '1':
          break;
        case '2': {
          node = new Node();
          graph->start = node;
          break;
        }
        case '3': {
          node = new Node();
          graph->end = node;
          break;
        }
      }

      if (node != nullptr) {
        node->adj = vector<pair<int, Node*>>();
        node->type = maze->matrix[i][j];
        node->x = j;
        node->y = i;

        nodes.push_back(node);
        nodeMatrix[i][j] = node;
      }
    }
  }

  for (Node* node : nodes) {
    vector<vector<bool>> visited(maze->n, vector<bool>(maze->m, false));
    getAdj(maze, nodeMatrix, node, visited, node->y, node->x, 0);
  }

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

  
  for (int i = 0; i < maze->n; i++) {
    for (int j = 0; j < maze->m; j++) {
      string c;
      switch (maze->matrix[i][j]) {
        case '0':
          c = "·";
          break;
        case '1':
          c = "■";
          break;
        case '2':
          c = "O";
          break;
        case '3':
          c = "X";
          break;
      }

      if(nodeMatrix[i][j] != nullptr)
        c = "#";
      cout << c << " ";
    }
    cout << endl;
  }

  return graph;
}