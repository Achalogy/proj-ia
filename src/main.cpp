#include <bits/stdc++.h>
#include <windows.h>

#include "./core/Execution.h"
#include "./implementations/menu/LoadMaze.h"

// Funciones de cada algoritmo

#include "./implementations/algorithms/AStar.h"
#include "./implementations/algorithms/BFS.h"
#include "./implementations/algorithms/DFS.h"
#include "./implementations/algorithms/Heuristica.h"

using namespace std;

int menu() {
  int opt = 0;

  do {
    cout << "1. Cargar laberinto" << endl;
    cout << "2. Ingresar salida y meta" << endl;
    cout << "3. Función en profundidad" << endl;
    cout << "4. Función en anchura" << endl;
    cout << "5. Función heurística" << endl;
    cout << "6. Funcion A*" << endl;
    cout << "7. Salir" << endl;

    cout << "> ";
    cin >> opt;
  } while (opt < 1 || opt > 7);

  return opt;
}

int main(void) {
  SetConsoleOutputCP(CP_UTF8);

  Execution execution;
  vector<Position>* resultado;

  while (true) {
    int opt = menu();

    switch (opt) {
      case 1:
        LoadMaze(&execution.maze);
        break;
      case 2: {
        cout << "Posición Inicio: " << endl;
        cout << "y = ";
        cin >> execution.start.y;
        cout << "x = ";
        cin >> execution.start.x;
        cout << endl;

        cout << "Posición Meta: " << endl;
        cout << "y = ";
        cin >> execution.end.y;
        cout << "x = ";
        cin >> execution.end.x;
        cout << endl;
        break;
      }
      case 3: {
        resultado = ExecuteDFS(execution);
        break;
      }
      case 4: {
        resultado = ExecuteBFS(execution);
        break;
      }
      case 5: {
        resultado = ExecuteHeuristica(execution);
        break;
      }
      case 6: {
        resultado = ExecuteAStar(execution);
        break;
      }
      case 7:
        return 0;
    }
  }
}