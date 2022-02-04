#include<stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

#include "Parser.h"
#include "PKB.h"
#include "TNode.cpp"
#include "Constants/Constants.h"
#include "Identifier.h"

/*
int const BASE_CASE = 0;
int const PROCEDURE = 1;
int const ASSIGN = 2;
int const ERROR = 3;
int const WHILE = 4;
int const IF_ELSE = 5;
int const READ = 6;
int const OPERATOR = 7;
int const PRINT = 8;
int const CALL = 9;
*/

Identifier identifier;
string extractFrontStringByRegex(string sourceCode, string regex);
TNode * recursiveTreeConstruction(string, TNode, int);
void convertToTNode(string);

int Parser::Parse (string filename) {
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
    convertToTNode(sourceCode);

    //extract relationship entities from AST
    //TODO: create a relationshipExtractor class to pull methods

    // transmit data to PKB

    return 0;
}

void convertToTNode(string sourceCode) {
    TNode firstNode = TNode("program");
    int static count = 1;
    // TODO (FUTURE): add a line number at the back of each statement (except 'then', 'else' & procedure_regex or blank)? for statement no. possibly Under StringFormatter
    recursiveTreeConstruction(sourceCode, firstNode, count);

}

// general idea: identify object, construct nodes, perform recursion with narrowed down code, trimmed stmt and repeat
TNode * recursiveTreeConstruction(string sourceCode, TNode currentNode, int stmtNo) {
    // insert recursion here
    //TODO: identifier + validation class to identify object type from SourceCode: Hong Wen
    //while(!sourceCode.empty()) {
        switch(identifier.identifyFirstObject(sourceCode)) { // identify object
            case PROCEDURE: {
                /*insert validation method here*/
                // build Nodes and pointers. add ref to current Node
                const string name = "Example"; // Hard coded stuff TODO: create an Extractor class that obtains important values like name & operators: Lucas.
                TNode newNode = TNode(name + ":procedure");
                currentNode.addNode(newNode);
                TNode childNode =  TNode("stmtList");
                newNode.addNode(childNode);

                // TODO: create a StringFormatter component that handles string trimming/partitioning. Lucas (later)
                // perform recursion on additional nodes
                //childNode.addNode( * recursiveTreeConstruction(sourceCode, childNode)); // not trimmed yet
                // remove stmts & syntax that are a part of this procedure_regex. while statement will loop again
                break;
            }
            case ASSIGN: {
                // add stmtNo as stmtNo to node
                cout << "assign found";
                stmtNo++;
                break;
            }

            case READ: {
                //add stmtNo as stmtNo to node
                cout << "read found";
                stmtNo++;
                break;
            }

            case PRINT: {
                //add stmtNo as stmtNo to node
                cout << "print found";
                stmtNo++;
                break;
            }

            case BASE_CASE: {
                cout << "base case found: " << sourceCode << "\n";
                break;
            }
            case OPERATOR: {
                cout << "operator found";
                break;
            }
            case ERROR: {
                break;
            }
        }
    //}
    return &currentNode;
}


