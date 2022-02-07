#include<stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

using namespace std;

#include "Parser.h"
#include "PKB.h"
#include "TNode.cpp"
#include "Constants/Constants.h"
#include "Constants/regex.h"
#include "Identifier.h"
#include "RelationshipExtractor.h"
#include "Extractor.h"
#include "StringFormatter.h"
#include "Partition.cpp"
#include "SourceTokenizer.h"


string emptyStr = "";
int statementNumber = 0;
Identifier identifier;
string extractFrontStringByRegex(string sourceCode, string regex);
TNode* recursiveTreeConstruction(string, TNode*&, int);
TNode convertToTNode(string);

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
    TNode * rootNodePtr;
    TNode rootNode = convertToTNode(sourceCode);
    rootNodePtr = &rootNode;

    //extract relationship entities from AST and transmit data to PKB
    //TODO: create a relationshipExtractor class to pull methods
    AssignNode* node = Parser::parseAssign(sourceCode);
    cout << node ->getRightNode() ->getVariableName() << "\n";
    cout << node ->getLeftNode() ->getVariableName() << "\n";
    //RelationshipExtractor::extractFollows(&rootNode);

    return 0;
}



TNode convertToTNode(string sourceCode) {
    TNode * firstNode;
    TNode node("program");
    firstNode = &node;

    int * count;
    int init = 1;
    count = &init;

    // TODO (FUTURE): add a line number at the back of each statement (except 'then', 'else' & procedure_regex or blank)? for statement no. possibly Under StringFormatter
    //firstNode = recursiveTreeConstruction(sourceCode, firstNode, init);
    return node;
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

TNode* recursiveTreeConstruction(string sourceCode, TNode * &currentNode, int stmtNo) {
    // insert recursion here
    string * sourcePtr;
    sourcePtr = &sourceCode;

    //TODO: identifier + validation class to identify object type from SourceCode: Hong Wen
    while(sourcePtr -> length() != 0) {
        StringFormatter stringFormatter;
        //Extractor extractor;
        TNode newNode = TNode(""); //Create empty new node to be filled in during switch and returned at the end
        switch(Identifier::identifyFirstObject(*sourcePtr)) { // identify object
            /*
            case ASSIGN: {
                //cout << "assign found\n";
                TNode * newNodePtr;
                newNodePtr = &newNode;
                Partition trimmedCode = stringFormatter.Trim(*sourcePtr, ASSIGN);
                newNode.changeValue("Assign ");

                //currentNode -> getNode(currentNode -> getNumberOfChildNodes() - 1) -> setStmtNo(stmtNo);
                newNodePtr ->setStmtNo(stmtNo);
                stmtNo++;

                // connecting current node to new node
                currentNode -> addNode(newNodePtr);

                string codeForTokenizing = trimmedCode.GetFirstString();
                vector<string> tokens;
                SourceTokenizer::extractAssign(codeForTokenizing, tokens);

                string varName = tokens[0];
                string expr = tokens[1];

                //pkb.addVariable(varname);

                TNode childNodeLeft = TNode(varName);
                newNode.addNode(&childNodeLeft);


                //cout << "newNodeValue: " << newNodePtr -> getValue()<< " | getStmtNo: " << newNodePtr -> getStmtNo() << "\n";
                //recursiveTreeConstruction(expr, newNodePtr, tempCount);

                //building other child nodes
                //extractor.extractAssign(codeToExtract)
                //TNode childNodeLeft = TNode(extractor.getAssignVar());
                //newNode.addNode(&childNodeLeft);
                //recursiveTreeConstruction(extractor.getAssignExpr(), newNode, ++stmtNo);

                //increment
                string codeToRecurse = trimmedCode.GetSecondString();
                sourcePtr = &codeToRecurse;
                break;
            }
            */
            case BASE_CASE: {
                TNode newNode = TNode(StringFormatter::removeTrailingSpace(*sourcePtr));
                currentNode -> addNode(&newNode);

                if (regex_match(*sourcePtr, std::regex(VAR_NAME))) {
                    //pkb.addVariable(*sourcePtr)
                }

                sourcePtr = &emptyStr;
                break;
            }
            case OPERATOR: {
                sourcePtr = &emptyStr;  // to immediately end the loop since this part not completed
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

    cout << "has stmtNo" << currentNode ->getNode(1) -> hasStmtNo() << "\n";
    return currentNode;
}



VariableNode* Parser::parseVar(string variable) {
    // convert into a variable node
    int check = Identifier::identifyFirstObject(variable);
    if(check == VARIABLE_NAME) {
        return new VariableNode(variable);
    } else {
        throw "Invalid varname format: '" + variable + "'\n";
    }
}

int getStatementNumber() {
    statementNumber = statementNumber + 1;
    return statementNumber;
}

AssignNode* Parser::parseAssign(string assignLine) {
    vector<string> tokens;
    SourceTokenizer::extractAssign(assignLine, tokens);
    return new AssignNode(getStatementNumber(), parseVar(tokens[0]), parseVar(tokens[1]));
}

// difficult to modify. edit at own risk
StatementList Parser::parseStatementList(string statementListString) {
    StatementList stmtLst;
    string * stmtLstPtr;
    stmtLstPtr = &statementListString;
    while(stmtLstPtr -> length() > 0) {
        StmtNode* newStmtNode = parseStatementNode(&*stmtLstPtr);
        stmtLst.push_back(newStmtNode);
    }
    return stmtLst;
}
StmtNode* Parser::parseStatementNode(string * stmt) {
    StmtNode * newNode;
    int switchCase = Identifier::identifyFirstObject(*stmt);
    switch(switchCase){
        case(ASSIGN): {
            vector<string> v = StringFormatter::Trim(*stmt, ASSIGN);
            newNode = Parser::parseAssign(v[0]);
            *stmt = v[1];
            break;
        }
            // ADD MORE CASES FOR STATEMENT
        default:{
            throw "cannot recognise '" + *stmt + "' as a statement";
            break;
        }
    }
    return newNode;
}