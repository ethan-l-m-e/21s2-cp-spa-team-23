#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#include "PKB.h"
#include "TNode.h"

int Parse (string filename) {
    // load file
    ifstream file;
    file.open(filename);
    // preferably throw exception if file invalid
    // extract text
    stringstream codeStream;
    codeStream << file.rdbuf();
    string sourceCode = codeStream.str();
    file.close();

    // proceed to convert sourceCode into AST using recursive descend
    return 0;
}


