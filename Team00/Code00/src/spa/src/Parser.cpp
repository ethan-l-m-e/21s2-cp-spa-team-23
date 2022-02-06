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
#include "RelationshipExtractor.h"
#include "Extractor.h"
#include "StringFormatter.h"
#include "Partition.cpp"

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
string emptyStr = EMPTY;
Identifier identifier;
string extractFrontStringByRegex(string sourceCode, string regex);
void recursiveTreeConstruction(string, TNode*, int*);
TNode* convertToTNode(string);

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
    TNode * rootNode = convertToTNode(sourceCode);

    //extract relationship entities from AST and transmit data to PKB
    //TODO: create a relationshipExtractor class to pull methods

    //RelationshipExtractor::extractRelationships();

    return 0;
}

TNode * convertToTNode(string sourceCode) {
    TNode * firstNode;
    TNode node("program");
    firstNode = &node;

    int * count;
    int init = 1;
    count = &init;

    // TODO (FUTURE): add a line number at the back of each statement (except 'then', 'else' & procedure_regex or blank)? for statement no. possibly Under StringFormatter
    recursiveTreeConstruction(sourceCode, firstNode, count);
    return firstNode;
}


// general idea: identify object, construct nodes, perform recursion with narrowed down code, trimmed stmt and repeat
/*
TNode * recursiveTreeConstruction(string sourceCode, TNode currentNode, int stmtNo) {
    // insert recursion here
    //TODO: identifier + validation class to identify object type from SourceCode: Hong Wen
    while(!sourceCode.empty()) {

        TNode newNode = TNode(""); //Create empty new node to be filled in during switch and returned at the end
        StringFormatter stringFormatter;
        Extractor extractor;
        switch(Identifier::identifyFirstObject(sourceCode)) { // identify object
            case PROCEDURE: {
                // build Nodes and pointers. add ref to current Node
                const string name = "Example"; // Hard coded stuff TODO: create an Extractor class that obtains important values like name & operators: Lucas.

                newNode.changeValue(name + ":procedure");
                currentNode.addNode(&newNode);
                TNode childNode =  TNode("stmtList");
                newNode.addNode(&childNode);
                extractor.extractProcedure(sourceCode);

                // TODO: create a StringFormatter component that handles string trimming/partitioning. Lucas (later)
                // perform recursion on additional nodes
                //childNode.addNode( * recursiveTreeConstruction(sourceCode, childNode)); // not trimmed yet
                // remove stmts & syntax that are a part of this procedure_regex. while statement will loop again
                break;
            }
            case ASSIGN: {
                cout << "assign found";
                Partition trimmedCode = stringFormatter.Trim(sourceCode, ASSIGN);
                string codeToExtract = trimmedCode.GetFirstString();
                string codeToRecurse = trimmedCode.GetSecondString();
                extractor.extractAssign(codeToExtract);
                newNode.changeValue("Assign");
                newNode.setStmtNo(stmtNo);
                TNode childNodeLeft = TNode(extractor.getAssignVar());
                TNode* childNodeRight = recursiveTreeConstruction(extractor.getAssignExpr(), newNode, ++stmtNo);
                newNode.addNode(&childNodeLeft);
                newNode.addNode(childNodeRight);
                sourceCode = codeToRecurse;
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

    }
    TNode * ptr;
    ptr = &newNode;
    return ptr;
}
*/

void recursiveTreeConstruction(string sourceCode, TNode * currentNode, int * stmtNo) {
    // insert recursion here
    string * sourcePtr;
    sourcePtr = &sourceCode;

    //TODO: identifier + validation class to identify object type from SourceCode: Hong Wen

    while(sourcePtr -> length() != 0) {
        TNode newNode = TNode(""); //Create empty new node to be filled in during switch and returned at the end
        StringFormatter stringFormatter;
        Extractor extractor;
        switch(Identifier::identifyFirstObject(*sourcePtr)) { // identify object
            case PROCEDURE: {
                // build Nodes and pointers. add ref to current Node
                const string name = "Example"; // Hard coded stuff TODO: create an Extractor class that obtains important values like name & operators: Lucas.
                newNode.changeValue(name + ":procedure");
                currentNode -> addNode(&newNode);
                TNode childNode =  TNode("stmtList");
                newNode.addNode(&childNode);
                extractor.extractProcedure(sourceCode);

                // TODO: create a StringFormatter component that handles string trimming/partitioning. Lucas (later)
                // perform recursion on additional nodes
                //childNode.addNode( * recursiveTreeConstruction(sourceCode, childNode)); // not trimmed yet
                // remove stmts & syntax that are a part of this procedure_regex. while statement will loop again
                sourcePtr = &emptyStr; // to immediately end the loop since this part not completed
                break;
            }
            case ASSIGN: {
                Partition trimmedCode = stringFormatter.Trim(*sourcePtr, ASSIGN);
                newNode.changeValue("Assign");
                newNode.setStmtNo(*stmtNo);

                // Node pointing
                currentNode -> addNode(&newNode);
                //extractor.extractAssign(codeToExtract)
                //TNode childNodeLeft = TNode(extractor.getAssignVar());
                //newNode.addNode(&childNodeLeft);
                //recursiveTreeConstruction(extractor.getAssignExpr(), newNode, ++stmtNo);

                (*stmtNo)++;
                string codeToRecurse = trimmedCode.GetSecondString();
                sourcePtr = &codeToRecurse;
                break;
            }
            case BASE_CASE: {
                newNode.changeValue(*sourcePtr);
                sourcePtr = &emptyStr; // to immediately end the loop since this part not completed
                break;
            }
            case OPERATOR: {
                sourcePtr = &emptyStr;
                break;
            }
            case ERROR: {
                sourcePtr = &emptyStr;
                break;
            }
            default:
                sourcePtr = &emptyStr;
                break;
        }
    }
}




