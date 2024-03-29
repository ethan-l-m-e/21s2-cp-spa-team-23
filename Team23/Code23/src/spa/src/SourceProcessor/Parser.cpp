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
#include "TNode/Node.cpp"
#include "Constants/Constants.h"
#include "Identifier.h"
#include "StringFormatter.h"
#include "SourceTokenizer.h"


string emptyStr = "";
int statementNumber = 0;
Identifier identifier;
string extractFrontStringByRegex(string sourceCode, string regex);

Node* Parser::Parse (string sourceCode) {
    auto programNode = parseProgram(sourceCode);
    return programNode;
}

VariableNode* Parser::parseVar(string input) {
    // convert into a variable node
    string variable = StringFormatter::removeMatchingFrontBackBrackets(input);
    int check = Identifier::identifyFirstObject(variable);
    if(check == VARIABLE_NAME) {
        return new VariableNode(variable);
    } else {
        throw InvalidSyntacticException("Invalid varname format: '" + variable + "'\n");
    }
}

ConstValueNode *Parser::parseConst(string input) {
    // convert into a const node
    string constValue = StringFormatter::removeMatchingFrontBackBrackets(input);
    int check = Identifier::identifyFirstObject(constValue);
    if(check == CONSTANT_VALUE) {
        return new ConstValueNode(constValue);
    } else {
        throw InvalidSyntacticException("Invalid const format: '" + constValue + "'\n");
    }
}

void Parser::resetStatementNumber() {
    statementNumber = 0;
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
Expression Parser::parseExpression(string expression) {
    expression = StringFormatter::removeTrailingSpace(StringFormatter::removeMatchingFrontBackBrackets(expression));
    if(!Identifier::checkParenthesesCorrectness(expression, "()"))
        throw InvalidSyntacticException("incorrect brackets in expression: " + expression + "\n");
    if (isLeaf(expression)) {
        if (isNumber(expression)) {
            return Parser::parseConst(expression);
        }
        return Parser::parseVar(expression);
    }
    vector<string> tokens;
    SourceTokenizer::extractExpression(expression, tokens);
    if(tokens[0] == "") throw InvalidSyntacticException("left side of binary operator cannot be empty");
    if(tokens[1] == "") throw InvalidSyntacticException("right side of binary operator cannot be empty");
    Expression left = parseExpression(tokens[0]);
    Expression right = parseExpression(tokens[1]);
    return new BinaryOperatorNode(left, right, tokens[2]);
}

CallNode *Parser::parseCall(string callLine) {
    int stmtNo = getStatementNumber();
    vector<string> tokens;
    SourceTokenizer::extractCall(callLine, tokens);
    ProcNameNode* newProcName = parseProcName(tokens[0]);

    return new CallNode(stmtNo, newProcName);
}

ReadNode *Parser::parseRead(string readLine) {
    int stmtNo = getStatementNumber();
    vector<string> tokens;
    SourceTokenizer::extractRead(readLine, tokens);
    VariableNode* newVar = parseVar(tokens[0]);

    return new ReadNode(stmtNo, newVar);
}

PrintNode *Parser::parsePrint(string printLine) {
    int stmtNo = getStatementNumber();
    vector<string> tokens;
    SourceTokenizer::extractPrint(printLine, tokens);
    VariableNode* newVar = parseVar(tokens[0]);

    return new PrintNode(stmtNo, newVar);
}

AssignNode* Parser::parseAssign(string assignLine) {
    int stmtNo = getStatementNumber();
    vector<string> tokens;
    SourceTokenizer::extractAssign(std::move(assignLine), tokens);
    VariableNode* newVarNode = parseVar(tokens[0]);
    Expression newExpression = parseExpression(tokens[1]);
    return new AssignNode(stmtNo, newVarNode, newExpression);
}

WhileNode *Parser::parseWhile(string code) {
    int stmtNo = getStatementNumber();
    vector<string> tokens;
    SourceTokenizer::extractWhile(code, tokens);
    CondExprNode* newCondExpr = parseCondExpr(tokens[0]);
    StatementList newStmtLst = parseStatementList(tokens[1]);

    return new WhileNode(stmtNo, newCondExpr, newStmtLst);
}

IfNode *Parser::parseIf(string code) {
    int stmtNo = getStatementNumber();
    vector<string> tokens;
    SourceTokenizer::extractIfElseThen(code, tokens);
    CondExprNode* newCondExpr = parseCondExpr(tokens[0]);
    StatementList newThenStmtLst = parseStatementList(tokens[1]);
    StatementList newElseStmtLst = parseStatementList(tokens[2]);

    return new IfNode(stmtNo, newCondExpr, newThenStmtLst, newElseStmtLst);
}

RelExprNode *Parser::parseRelExpr(string relExprLine) {
    relExprLine = StringFormatter::removeTrailingSpace(StringFormatter::removeMatchingFrontBackBrackets(relExprLine));
    vector<string> tokens;
    SourceTokenizer::extractRelExpr(relExprLine, tokens);
    RelFactor newLeftRelFactor = parseExpression(tokens[0]);
    RelFactor newRightRelFactor = parseExpression(tokens[1]);
    return new RelExprNode(newLeftRelFactor, newRightRelFactor, tokens[2]);
}

CondExprNode *Parser::parseCondExpr(string condExprLine) {
    condExprLine = StringFormatter::removeTrailingSpace(StringFormatter::removeMatchingFrontBackBrackets(condExprLine));
    vector<string> tokens;
    SourceTokenizer::extractCondExpr(std::move(condExprLine), tokens);
    if (tokens[0].empty()) {
        RelExprNode* newRelExpr = parseRelExpr(tokens[2]);
        return new CondExprNode(newRelExpr);
    }
    if (tokens[0] == "!") {
        CondExprNode* newCondExpr = parseCondExpr(tokens[2]);
        return new CondExprNode(newCondExpr);
    }
    CondExprNode* newLeftCondExpr = parseCondExpr(tokens[1]);
    CondExprNode* newRightCondExpr = parseCondExpr(tokens[2]);
    return new CondExprNode(tokens[0],newLeftCondExpr, newRightCondExpr);
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
            vector<string> v = SourceTokenizer::partitionAccordingToCase(*stmt, ASSIGN);
            newNode = Parser::parseAssign(v[0]);
            *stmt = StringFormatter::removeTrailingSpace(v[1]);
            break;
        }
        case(WHILE): {
            vector<string> v = SourceTokenizer::partitionAccordingToCase(*stmt, WHILE);
            newNode = Parser::parseWhile(v[0]);
            *stmt = StringFormatter::removeTrailingSpace(v[1]);
            break;
        }
        case(READ): {
            vector<string> v = SourceTokenizer::partitionAccordingToCase(*stmt, READ);
            newNode = Parser::parseRead(v[0]);
            *stmt = StringFormatter::removeTrailingSpace(v[1]);
            break;
        }
        case(PRINT): {
            vector<string> v = SourceTokenizer::partitionAccordingToCase(*stmt, PRINT);
            newNode = Parser::parsePrint(v[0]);
            *stmt = StringFormatter::removeTrailingSpace(v[1]);
            break;
        }
        case(IF_ELSE): {
            vector<string> v = SourceTokenizer::partitionAccordingToCase(*stmt, IF_ELSE);
            newNode = Parser::parseIf(v[0]);
            *stmt = StringFormatter::removeTrailingSpace(v[1]);
            break;
        }
        case(CALL): {
            vector<string> v = SourceTokenizer::partitionAccordingToCase(*stmt, CALL);
            newNode = Parser::parseCall(v[0]);
            *stmt = StringFormatter::removeTrailingSpace(v[1]);
            break;
        }
        default:{
            throw "cannot recognise '" + *stmt + "' as a statement";
            break;
        }
    }
    return newNode;
}

ProcNameNode *Parser::parseProcName(string procedureName) {
    return new ProcNameNode(procedureName);
}

ProcedureNode *Parser::parseProcedure(string * procedure) {
    vector<string> v = SourceTokenizer::partitionAccordingToCase(*procedure, PROCEDURE);
    vector<string> tokens;
    SourceTokenizer::extractProcedure(v[0], tokens);
    *procedure = StringFormatter::removeTrailingSpace(v[1]);
    ProcNameNode* newProcNameNode = Parser::parseProcName(tokens[0]);
    StatementList stmtLst = parseStatementList(tokens[1]);
    return new ProcedureNode(newProcNameNode, stmtLst);
}

ProgramNode* Parser::parseProgram(string sourceCode) {
    vector<string> tokens;
    ProcedureList newProcLst;
    string * procedurePtr;
    procedurePtr = &sourceCode;
    while(procedurePtr->length() > 0) {
        ProcedureNode *newProcedureNode = Parser::parseProcedure(procedurePtr);
        newProcLst.push_back(newProcedureNode);
    }
    return new ProgramNode(newProcLst);
}
