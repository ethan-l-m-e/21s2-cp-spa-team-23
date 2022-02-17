//
// Created by Tin Hong Wen on 5/2/22.
//
#include "iostream"
#include "RelationshipExtractor.h"
#include "TNode.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("test follows - basic") {
    VariableNode v1 = VariableNode("y");
    VariableNode* varPtrY = &v1;
    VariableNode v2 = VariableNode("x");
    VariableNode* varPtrX = &v2;
    VariableNode v3 = VariableNode("a");
    VariableNode* varPtrA = &v3;
    VariableNode v4 = VariableNode("b");
    VariableNode* varPtrB = &v4;
    RelExprNode relNode = RelExprNode(varPtrX,varPtrY,"<");
    RelExprNode* relPtr = &relNode;
    CondExprNode defaultCond = CondExprNode(relPtr);
    CondExprNode* condPtr = &defaultCond;
    StatementList emptyStmtLst = {};

//    Node pNode = Node();
    Node aNode= AssignNode(1,varPtrX,varPtrY);
    Node bNode= AssignNode(2,varPtrA,varPtrB);
    StatementList defaultStmtLst;
    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);

    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);

    ProcNameNode p = ProcNameNode("test");
    ProcedureNode pNode = ProcedureNode(0, &p, defaultStmtLst);
    cout<<defaultStmtLst.size();
    cout<<"\n";
    RelationshipExtractor::extractFollows(&pNode);

    REQUIRE("fail" == "test");

//    Node cNode("read:x", 6);
//    Node dNode("cond");
//    Node eNode("assign", 4);
//    Node fNode("print:x", 5);

    /*
    pNode.addNode(&aNode);
    pNode.addNode(&bNode);
    pNode.addNode(&cNode);

    bNode.addNode(&dNode);
    bNode.addNode(&eNode);
    bNode.addNode(&fNode);
    */

//    RelationshipExtractor::extractFollows(&pNode);
}