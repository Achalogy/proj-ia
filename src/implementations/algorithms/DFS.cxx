#include <bits/stdc++.h>
#include "../../core/Execution.h"
#include "DFS.h"

using namespace std;


bool dfsHelper(int u, int target, Graph* graph, vector<bool>& visited, map<int, int>& parent) {
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

vector<Position>* ExecuteDFS(Execution* execution) {
    if (!execution->graph) {
        cout << "No hay un grafo cargado." << endl;
        return nullptr;
    }

    Graph* g = execution->graph;
    int startId = g->start->id;
    int endId = g->end->id;

    // Inicializamos estructuras
    vector<bool> visited(g->nodes.size(), false);
    map<int, int> parent;
    vector<Position>* path = new vector<Position>();

    if (dfsHelper(startId, endId, g, visited, parent)) {
        
        int curr = endId;
        while (curr != startId) {
            path->push_back({g->nodes[curr]->y, g->nodes[curr]->x});
            curr = parent[curr];
        }
        path->push_back({g->nodes[startId]->y, g->nodes[startId]->x});

        
        reverse(path->begin(), path->end());
        
        cout << "DFS: Se encontro un camino de " << path->size() << " nodos." << endl;
        PrintPath(path, g->maze->n, g->maze->m);
    } else {
        cout << "DFS: No existe un camino entre el inicio y la salida." << endl;
    }

    return path;
}

void PrintPath(vector<Position>* path, int rows, int cols) {
    if (path->empty()) return;

    
    vector<vector<char>> visual(rows, vector<char>(cols, '.'));

    for (const auto& p : *path) {
        visual[p.y][p.x] = '*';
    }

    cout << "\nVisualizacion del camino (DFS):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << visual[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}