#ifndef DFS_H
#define DFS_H

#include <vector>
#include "../../core/Execution.h"


vector<Position>* ExecuteDFS(Execution* execution);


void PrintPath(vector<Position>* path, int rows, int cols);

#endif