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

TEST_CASE("Assign parsing") {
    string left = "x";
    string right = "randomVariable";
    string input = left + " = " + right + ";";
    AssignNode * testNode = Parser::parseAssign(input);
    CHECK(left ==  testNode ->getLeftNode() ->getVariableName());
    CHECK(right == testNode ->getRightNode() ->getVariableName());
}
