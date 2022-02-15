#include<stdio.h>
#include <iostream>
#include <utility>
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
//#include "RelationshipExtractor.h"
#include "Extractor.h"
#include "StringFormatter.h"
#include "Partition.cpp"
#include "SourceTokenizer.h"


string emptyStr = "";
int statementNumber = 0;
Identifier identifier;
string extractFrontStringByRegex(string sourceCode, string regex);

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



    //extract relationship entities from AST and transmit data to PKB
    //TODO: create a relationshipExtractor class to pull methods
    StatementList statementList = Parser::parseStatementList(sourceCode);

    //RelationshipExtractor::extractFollows(&rootNode);

    return 0;
}

VariableNode* Parser::parseVar(string variable) {
    // convert into a variable node
    int check = Identifier::identifyFirstObject(variable);
    if(check == VARIABLE_NAME) {
        cout << "sending var " << variable << " to PKB\n";
        PKB::getInstance() ->addVariable(variable);
        return new VariableNode(variable);
    } else {
        throw "Invalid varname format: '" + variable + "'\n";
    }
}

ConstValueNode *Parser::parseConst(string constValue) {
    // convert into a const node
    int check = Identifier::identifyFirstObject(constValue);
    if(check == CONSTANT_VALUE) {
        cout << "sending const " << constValue << " to PKB\n";
        PKB::getInstance() ->addConstant(constValue);
        return new ConstValueNode(constValue);
    } else {
        throw "Invalid const format: '" + constValue + "'\n";
    }
}

int getStatementNumber() {
    statementNumber = statementNumber + 1;
    return statementNumber;
}

bool isLeaf(const string& expression) {
    if (expression.find('+') != string::npos
        || expression.find('-') != string::npos
        || expression.find('*') != string::npos
        || expression.find('/') != string::npos
        || expression.find('%') != string::npos) {
        return false;
    }
    return true;
}
bool isNumber(string s) {
    for(char const &c: s) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}
Expression parseExpression(string expression) {
    if (isLeaf(expression)) {
        if (isNumber(expression)) {
            return Parser::parseConst(expression);
        }
        return Parser::parseVar(expression);
    }
    vector<string> tokens;
    SourceTokenizer::extractExpression(expression, tokens);
    Expression left = parseExpression(tokens[0]);
    Expression right = parseExpression(tokens[1]);
    return new BinaryOperatorNode(left, right, tokens[2]);
}

AssignNode* Parser::parseAssign(string assignLine) {
    vector<string> tokens;
    SourceTokenizer::extractAssign(std::move(assignLine), tokens);
    VariableNode* newVarNode = parseVar(tokens[0]);
    Expression newExpression = parseExpression(tokens[1]);
    int stmtNo = getStatementNumber();
    cout << "sending assign " << stmtNo << " to PKB\n";
    PKB::getInstance()->addAssignStatement(stmtNo);
    return new AssignNode(stmtNo, newVarNode, newExpression);
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
            /*
        case(WHILE): {
            vector<string> v = StringFormatter::Trim(*stmt, WHILE);
            newNode = Parser::parseWhile(v[0]);
            *stmt = v[1];
            break;
        }
        case(IF_ELSE): {
            vector<string> v = StringFormatter::Trim(*stmt, IF_ELSE);
            newNode = Parser::parseIf(v[0]);
            *stmt = v[1];
            break;
        }
        case(READ): {
            vector<string> v = StringFormatter::Trim(*stmt, READ);
            newNode = Parser::parseRead(v[0]);
            *stmt = v[1];
            break;
        }
        case(PRINT): {
            vector<string> v = StringFormatter::Trim(*stmt, PRINT);
            newNode = Parser::parsePrint(v[0]);
            *stmt = v[1];
            break;
        }
             */
        default:{
            throw "cannot recognise '" + *stmt + "' as a statement";
            break;
        }
    }
    return newNode;
}

ProcNameNode *Parser::parseProcName(string procedureName) {
    //int check = Identifier::identifyFirstObject(procedureName);
    //if(check == PROCEDURE_NAME) {
        cout << "sending proc " << procedureName << " to PKB\n";
        PKB::getInstance() ->addProcedure(procedureName);
        return new ProcNameNode(procedureName);
    //} else {
        throw "Invalid varname format: '" + procedureName + "'\n";
    //}
}

ProcedureNode *Parser::parseProcedure(string * procedure) {
    //vector<string> v = StringFormatter::Trim(*procedure, PROCEDURE);
    // REPLACE WITH ABOVE ONCE IMPLEMENTED
    vector<string> v;
    v.push_back(*procedure);
    v.push_back("");
    // ---------------------------------- //

    vector<string> tokens;
    SourceTokenizer::extractProcedure(v[0], tokens);
    *procedure = v[1];
    ProcNameNode* newProcNameNode = Parser::parseProcName(tokens[0]);
    StatementList stmtLst = parseStatementList(tokens[1]);
    return new ProcedureNode(newProcNameNode, stmtLst);
}

Program Parser::parseProgram(string sourceCode) {
    vector<string> tokens;
    Program program;
    string * procedurePtr;
    procedurePtr = &sourceCode;
    //while(procedurePtr -> length() > 0) {
        ProcedureNode *newProcedureNode = Parser::parseProcedure(&sourceCode);
        program.push_back(newProcedureNode);
    //}
    return program;
}
