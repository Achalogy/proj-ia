#include <bits/stdc++.h>
#include <windows.h>

#include "./core/Execution.h"
#include "./implementations/menu/LoadMaze.h"
#include "./implementations/menu/MatrixToGraph.h"
#include "./utils/PrintPath.h"
#include "./utils/StepPrint.h"
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
    cout << "5. Salir" << endl;

    cout << "> ";
    cin >> opt;
  } while (opt < 1 || opt > 6);

  return opt;
}

int main(void) {
  // Manejar todos los caracteres y tildes
  SetConsoleOutputCP(CP_UTF8);

  Execution* execution = new Execution();
  vector<Node*>* result;

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
        StepPrint(result, execution);
        break;
      }
      case 3: {
        result = ExecuteBFS(execution);
        StepPrint(result, execution);
        break;
      }
      case 4: {
        result = ExecuteAStar(execution);
        StepPrint(result, execution);
        break;
      }
      case 5:
        return 0;
    }
  }

  delete execution;
  delete[] result;
}