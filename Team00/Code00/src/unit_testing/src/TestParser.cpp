//
// Created by Tin Hong Wen on 7/2/22.
//
#include <iostream>

#include "Parser.h"
#include "catch.hpp"
using namespace std;



TEST_CASE("Statement List parsing") {
    string stmt1 = "x = y;\n";
    string stmt2 = "y = z;\n";
    string stmt3 = "a = b;\n";
    string stmt4 = "c = d;\n";
    string stmt5 = "e = f;";

    string testList = stmt1 + stmt2 + stmt3 + stmt4 + stmt5;
    StatementList resultList = Parser::parseStatementList(testList);

    CHECK(1 == resultList[0] ->getStmtNumber());
    CHECK(2 == resultList[1] ->getStmtNumber());
    CHECK(3 == resultList[2] ->getStmtNumber());
    CHECK(4 == resultList[3] ->getStmtNumber());
    CHECK(5 == resultList[4] ->getStmtNumber());
    string testList2 = stmt1 + stmt2 + stmt3 + stmt4 + stmt5;
    StatementList resultList2 = Parser::parseStatementList(testList);

    CHECK(6 == resultList2[0] ->getStmtNumber());
    CHECK(7 == resultList2[1] ->getStmtNumber());
    CHECK(8 == resultList2[2] ->getStmtNumber());
    CHECK(9 == resultList2[3] ->getStmtNumber());
    CHECK(10 == resultList2[4] ->getStmtNumber());
}

TEST_CASE("Statement parsing") {
    string x = "x";
    string y = "y";
    string stmt1 = x + " = " + y + ";";
    string stmt2 = "y = z;";
    string stmt3 = "read print;";
    string stmt4 = stmt1 + "\n" + stmt2 + "\n" + stmt3;
    string * ptr;
    ptr = &stmt4;
    StmtNode * testNode1 = Parser::parseStatementNode(&*ptr);
    StmtNode * testNode2 = Parser::parseStatementNode(&*ptr);

    CHECK(*ptr == stmt3);
    CHECK(1 == testNode1 -> getStmtNumber());
    CHECK(2 == testNode2 -> getStmtNumber());
}

TEST_CASE("Read parsing") {
    string readLine = "read x;";
    auto testNode = Parser::parseRead(readLine);
    CHECK(testNode->getVarName() == "x");
}

TEST_CASE("Print parsing") {
    string printLine = "print x;";
    auto testNode = Parser::parsePrint(printLine);
    CHECK(testNode->getVarName() == "x");
}

TEST_CASE("Assign parsing") {
    string left = "x";
    string right = "randomVariable";
    string input = left + " = " + right + ";";
    AssignNode * testNode = Parser::parseAssign(input);
    CHECK(left ==  testNode ->getLeftNode() ->getVariableName());
    CHECK(right == get<VariableNode*>(testNode ->getRightNode())->getVariableName());
    CHECK(testNode->getStmtNumber() == 1);
}

TEST_CASE("Assign parsing with expression") {
    string left = "x";
    string var1 = "y";
    string constant = "2";
    string var2 = "randomVariable";
    string right = var1 + " + " + constant + " * " + var2;
    string input = left + " = " + right + ";";
    AssignNode * testNode = Parser::parseAssign(input);
    CHECK(left ==  testNode ->getLeftNode() ->getVariableName());
    auto expr = get<BinaryOperatorNode*>(testNode->getRightNode());
    CHECK(expr->getBinaryOperator() == "+");
    CHECK(get<VariableNode*>(expr->getLeftExpr())->getVariableName() == var1);
    CHECK(get<BinaryOperatorNode*>(expr->getRightExpr())->getBinaryOperator() == "*");
    CHECK(get<ConstValueNode*>(get<BinaryOperatorNode*>(expr->getRightExpr())->getLeftExpr())->getConstValue() == constant);
    CHECK(get<VariableNode*>(get<BinaryOperatorNode*>(expr->getRightExpr())->getRightExpr())->getVariableName() == var2);
    CHECK(testNode->getStmtNumber() == 1);
}

TEST_CASE("While parsing") {
    string code = "while (number > 0) { X = a;\nwhile (number > 0) { X = a; } } X = a;";
    Parser::parseStatementNode(&code);
}

TEST_CASE("Relative expression parsing") {
    cout << "Check less than equals\n";
    string relExprString = "X <= Y * 1";
    RelExprNode* testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == "<=");
    CHECK(get<VariableNode*>(testNode->getLeftFactor())->getVariableName() == "X");
    CHECK(get<BinaryOperatorNode*>(testNode->getRightFactor())->getBinaryOperator() == "*");
    CHECK(get<VariableNode*>(get<BinaryOperatorNode*>(testNode->getRightFactor())->getLeftExpr())->getVariableName() == "Y");
    CHECK(get<ConstValueNode*>(get<BinaryOperatorNode*>(testNode->getRightFactor())->getRightExpr())->getConstValue() == "1");

    cout << "Check greater than equals\n";
    relExprString = "X >= Y * 1";
    testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == ">=");

    cout << "Check less than\n";
    relExprString = "X < Y * 1";
    testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == "<");

    cout << "Check greater than\n";
    relExprString = "X > Y * 1";
    testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == ">");

    cout << "Check less than\n";
    relExprString = "X < Y * 1";
    testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == "<");

    cout << "Check equals\n";
    relExprString = "X == Y * 1";
    testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == "==");

    cout << "Check not equals\n";
    relExprString = "X != Y * 1";
    testNode = Parser::parseRelExpr(relExprString);
    CHECK(testNode->getRelativeOperator() == "!=");
}

TEST_CASE("Condition expression parsing") {
    cout << "Check && expr\n";
    string condExprString = "A == a && B > b";
    auto testNode = Parser::parseCondExpr(condExprString);
    CHECK(testNode->getCondOperator() == "&&");

    cout << "Check || expr\n";
    condExprString = "A == a || B > b";
    testNode = Parser::parseCondExpr(condExprString);
    CHECK(testNode->getCondOperator() == "||");

    cout << "Check ! expr\n";
    condExprString = "! B > b";
    testNode = Parser::parseCondExpr(condExprString);
    CHECK(testNode->getCondOperator() == "!");

    cout << "Check rel expr\n";
    condExprString = "B > b";
    testNode = Parser::parseCondExpr(condExprString);
    CHECK(testNode->getCondOperator().empty());
}

TEST_CASE("Program parsing") {
    string code = "procedure name { X = a;\nread b;\nprint c;\n }";
    Program program = Parser::parseProgram(code);
    CHECK(program[0]->getProcName() == "name");
}
