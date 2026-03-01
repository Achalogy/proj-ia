#include <bits/stdc++.h>

#include "../core/Execution.h"
#include "PrintPath.h"

using namespace std;

void StepPrint(vector<Node*>* path, Execution* execution) {
  int lim = 1;

  while(lim <= path->size()) {

    vector<Node *> _path = vector<Node *>(path->begin(), path->begin() + lim);

    cout << "Paso #" << lim << "/" << path->size() << endl;
    PrintPath(&_path, execution);
    cin.ignore();
    cout << endl;

    lim++;
  }

}