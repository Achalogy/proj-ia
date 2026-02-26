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

// Función para convertir una matriz a una estructura de grafo usando apuntadores.
Graph* MatrixToGraph(Maze* maze) {
  Graph* graph = new Graph();

  graph->start = nullptr;
  graph->end = nullptr;

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

      // Revisión de los datos tomados para el correcto funcionamiento del sistema.
      if (node->type == '2') {
        if (graph->start != nullptr) {
          cout << "Grafo invalido, multiples nodos de inicio" << endl;

          delete graph;
          return nullptr;
        }
        graph->start = node;
      }
      if (node->type == '3') {
        if (graph->end != nullptr) {
          cout << "Grafo invalido, multiples nodos de salida" << endl;

          delete graph;
          return nullptr;
        }
        graph->end = node;
      }
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

  cout << graph << endl;
  return graph;
}