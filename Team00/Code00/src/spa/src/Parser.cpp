#include<stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

#include "Parser.h"
#include "PKB.h"
#include "TNode.cpp"
#include "Constants.h"

/*
int const BASE_CASE = 0;
int const PROCEDURE = 1;
int const ASSIGN = 2;
int const ERROR = 3;
int const WHILE = 4;
int const IF = 5;
int const READ = 6;
int const OPERATOR = 7;
int const PRINT = 8;
int const CALL = 9;
*/

string extractFrontStringByRegex(string sourceCode, string regex);
TNode * recursiveTreeConstruction(string, TNode);
void convertToTNode(string);
int identifyFirstObject(string line);

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
\
    //extract relationship entities from AST
    //TODO: create a relationshipExtractor class to pull methods
    return 0;
}



void convertToTNode(string sourceCode) {
    TNode firstNode = TNode("program");
    // TODO (FUTURE): add a line number at the back of each statement (except 'then', 'else' & procedure_regex or blank)? for statement no. possibly Under StringFormatter
    recursiveTreeConstruction(sourceCode, firstNode);

}

// general idea: identify object, construct nodes, perform recursion with narrowed down code, trimmed stmt and repeat
TNode * recursiveTreeConstruction(string sourceCode, TNode currentNode) {
    // insert recursion here
    //TODO: identifier + validation class to identify object type from SourceCode: Hong Wen
    //while(!sourceCode.empty()) {
        switch(identifyFirstObject(sourceCode)) { // identify object
            case PROCEDURE: {
                cout << "procedure_regex found\n";
                /*insert validation method here*/
                // build Nodes and pointers. add ref to current Node
                const string name = "Example"; // Hard coded stuff TODO: create an Extractor class that obtains important values like name & operators: Lucas.
                TNode newNode = TNode(name + ":procedure");
                currentNode.addNode(newNode);
                TNode childNode =  TNode("stmtList");
                newNode.addNode(childNode);

                // TODO: create a StringFormatter component that handles string trimming/partitioning. Lucas (later)
                // perform recursion on additional nodes
                childNode.addNode( * recursiveTreeConstruction(sourceCode, childNode)); // not trimmed yet
                // remove stmts & syntax that are a part of this procedure_regex. while statement will loop again
                break;
            }
            case ASSIGN: {
                cout << "assign found";
                break;
            }
            case BASE_CASE: {
                cout << "base case found: " << " y";
                break;
            }
            case OPERATOR: {
                cout << "operator found";
                break;
            }
            case ERROR: {

            }
        }


    //}
    return &currentNode;
}



// checks
int identifyFirstObject(string line) {
    // TODO: IDENTIFIER (+ validator) CLASS to determine object/node type. if identified, check if the basic syntax holds?
    const char *lineChar = line.c_str();

    if(regex_match(line, std::regex(procedure))) {
        return PROCEDURE;
    } else if (strstr(lineChar, assign.c_str()) != nullptr) {
        return ASSIGN;
    } else {
        cout << "cannot identify Object type. ERROR.";
        return 123213;
    }

}

string extractFrontStringByRegex(string sourceCode, string regex) {
    char * sourceAsChar = new char[100];
    char * regexChar = new char[100];
    strcpy(sourceAsChar, sourceCode.c_str());
    strcpy(regexChar, regex.c_str());
    char *token = strtok(sourceAsChar,regexChar);
    string s(token);
    return s;
}