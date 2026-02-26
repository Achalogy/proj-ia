#include <bits/stdc++.h>
#include <windows.h>

#include "./core/Execution.h"
#include "./implementations/menu/LoadMaze.h"
#include "./implementations/menu/MatrixToGraph.h"
#include "./utils/PrintPath.h"

// Funciones de cada algoritmo

#include "./implementations/algorithms/AStar.h"
#include "./implementations/algorithms/BFS.h"
#include "./implementations/algorithms/DFS.h"

using namespace std;

int menu() {
  int opt = 0;

  do {
    cout << "1. Cargar laberinto" << endl;
    cout << "2. Función en profundidad" << endl;
    cout << "3. Función en anchura" << endl;
    cout << "4. Funcion A*" << endl;
    cout << "6. Salir" << endl;

    cout << "> ";
    cin >> opt;
  } while (opt < 1 || opt > 7);

  return opt;
}

int main(void) {
  SetConsoleOutputCP(CP_UTF8);

  Execution* execution = new Execution();
  vector<Position>* result;

  while (true) {
    int opt = menu();

    switch (opt) {
      case 1: {
        Maze* maze = new Maze();
        LoadMaze(maze);
        execution->graph = MatrixToGraph(maze);
        break;
      }
      case 2: {
        result = ExecuteDFS(execution);
        PrintPath(result, execution);
        break;
      }
      case 3: {
        result = ExecuteBFS(execution);
        PrintPath(result, execution);
        break;
      }
      case 4: {
        result = ExecuteAStar(execution);
        PrintPath(result, execution);
        break;
      }
      case 6:
        return 0;
    }
  }

  delete execution;
  delete[] result;
}