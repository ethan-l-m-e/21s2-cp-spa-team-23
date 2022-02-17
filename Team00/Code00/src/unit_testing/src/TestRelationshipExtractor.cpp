//
// Created by Tin Hong Wen on 5/2/22.
//
#include "iostream"
#include "RelationshipExtractor.h"
#include "TNode.h"
#include "catch.hpp"
#include "PKB.h"

using namespace std;

VariableNode v1 = VariableNode("y");
VariableNode v2 = VariableNode("x");
VariableNode v3 = VariableNode("a");
VariableNode v4 = VariableNode("b");
RelExprNode relNode = RelExprNode(&v2,&v1,"<");
RelExprNode* relPtr = &relNode;
CondExprNode defaultCond = CondExprNode(relPtr);
CondExprNode* condPtr = &defaultCond;
StatementList emptyStmtLst = {};

//    Node pNode = Node();
StmtNode aNode= AssignNode(1,&v2,&v1);
StmtNode bNode= AssignNode(2,&v3,&v4);
StmtNode cNode= AssignNode(3,&v1,&v4);
StmtNode dNode= AssignNode(5,&v2,&v3);
StmtNode eNode= AssignNode(6,&v4,&v1);
StatementList defaultStmtLst;
StatementList defaultStmtLst2;


ProcNameNode p = ProcNameNode("test");

TEST_CASE("test follows - basic") {
    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);
    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollows(1,2));
    REQUIRE(PKB::getInstance()->isFollows(2,3));
}

TEST_CASE("test follows - fail test") {
    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollows(0,2)==false);
    REQUIRE(PKB::getInstance()->isFollows(1,3)==false);
}

TEST_CASE("test follows* - basic") {
    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollowsT(1,3));
}

//pkb parents doesnt seem to work yet so these will fail
TEST_CASE("test parents - basic") {
    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&pNode);
    RelationshipExtractor::extractParent(&pNode,v);
    REQUIRE(PKB::getInstance()->isParent(0,2));
}

TEST_CASE("test parents - fail") {
    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&pNode);
    RelationshipExtractor::extractParent(&pNode,v);
    REQUIRE(PKB::getInstance()->isParent(1,2));
}

TEST_CASE("test parents* - basic") {
    StatementList nestedStatementList;
    nestedStatementList.push_back(&aNode);
    nestedStatementList.push_back(&bNode);

    WhileNode wNode = WhileNode(3, condPtr, defaultStmtLst2);
    nestedStatementList.push_back(&wNode);

    ProcedureNode pNode = ProcedureNode(&p, nestedStatementList);

    vector<StmtLstNode*> v;
    v.push_back(&pNode);
    RelationshipExtractor::extractParent(&pNode,v);
    REQUIRE(PKB::getInstance()->isParent(0,2));
}


TEST_CASE("test") {
    PKB::getInstance()->setParent(0,1);
    REQUIRE(PKB::getInstance()->isParent(0,1));
}