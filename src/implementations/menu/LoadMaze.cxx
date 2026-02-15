#include "../../core/Maze.h"
#include <bits/stdc++.h>
using namespace std;

void LoadMaze(Maze *maze)
{
    string filename = "";

    cout << "Nombre del archivo: ";
    cin >> filename;

    ifstream mazeFile(filename);
    
    mazeFile >> maze->n;
    mazeFile >> maze->m;

    if(maze->n < 0 || maze->m < 0) {
        cout << "Matriz con tamaño invalido" << endl;
        return;
    }

    maze->matrix = new char*[maze->n]; // Filas

    for(int i = 0; i < maze->n; i++) {
        // Crear la fila con maze->m elementos
        // *(maze->matrix + i) = new char[maze->m]; 
        maze->matrix[i] = new char[maze->m];
        
        for(int j = 0; j < maze->m; j++) {
            char c; mazeFile >> c;

            if(c != '0' && c != '1' && c != '2' && c != '3' ){
                cout << "Ingresaste un valor inválido, intenta de nuevo." << endl;
                
                delete[] maze->matrix;
                maze->matrix = nullptr;
                
                return;
            }

            maze->matrix[i][j] = c;

        }


    }

    cout << "Matriz del laberinto cargada con éxito :)" << endl;

    if(maze->n <= 25 && maze->m <= 25 ) {
        for(int i = 0; i < maze->n; i++) {
            for(int j = 0; j < maze->m; j++) {
                cout << maze->matrix[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Matriz muy grande para poder mostrarla" << endl;
    }

}