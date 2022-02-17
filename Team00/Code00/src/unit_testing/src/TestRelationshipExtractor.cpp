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

auto aNode= AssignNode(1,&v2,&v1);
auto bNode= AssignNode(2,&v3,&v4);
auto cNode= AssignNode(3,&v1,&v4);
auto dNode= AssignNode(5,&v2,&v3);
auto eNode= AssignNode(6,&v4,&v1);

ProcNameNode p = ProcNameNode("test");

TEST_CASE("test follows - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollows("1","2"));
    REQUIRE(PKB::getInstance()->isFollows("2","3"));
}

TEST_CASE("test follows - fail test") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollows("0","2")==false);
    REQUIRE(PKB::getInstance()->isFollows("1","3")==false);
}

TEST_CASE("test follows* - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollowsT("1","3"));
}

//pkb parents doesnt seem to work yet so these will fail
TEST_CASE("test parents - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&pNode);
    RelationshipExtractor::extractParent(&pNode,v);
    REQUIRE(PKB::getInstance()->isParent("0","2"));
}

TEST_CASE("test parents - fail") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&pNode);
    RelationshipExtractor::extractParent(&pNode,v);
    REQUIRE(PKB::getInstance()->isParent("1","2"));
}

TEST_CASE("test parents* - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    StatementList nestedStatementList;
    nestedStatementList.push_back(&aNode);
    nestedStatementList.push_back(&bNode);
    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    WhileNode wNode = WhileNode(3, condPtr, defaultStmtLst2);
    nestedStatementList.push_back(&wNode);

    ProcedureNode pNode = ProcedureNode(&p, nestedStatementList);

    vector<StmtLstNode*> v;
    v.push_back(&pNode);
    RelationshipExtractor::extractParent(&pNode,v);
    REQUIRE(PKB::getInstance()->isParent("0","2"));
}

TEST_CASE("test uses - basic") {
    RelationshipExtractor::extractUses(&aNode);
    REQUIRE(PKB::getInstance()->isUses("1","y"));
}

TEST_CASE("test uses - container statement") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst3;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);
    defaultStmtLst3.push_back(&dNode);
    defaultStmtLst3.push_back(&eNode);

    auto wNode = WhileNode(3, condPtr, defaultStmtLst3);
    RelationshipExtractor::extractUses(&wNode);
    REQUIRE(PKB::getInstance()->isUses("3","a"));
}
TEST_CASE("test modifies - basic") {
    RelationshipExtractor::extractModifies(&aNode);
    REQUIRE(PKB::getInstance()->isModifies("1","x"));
}

TEST_CASE("test Modifies - container statement") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst4;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);
    defaultStmtLst4.push_back(&dNode);
    defaultStmtLst4.push_back(&eNode);
    auto wNode = WhileNode(3, condPtr, defaultStmtLst4);
    cout<<defaultStmtLst4.size();
    RelationshipExtractor::extractModifies(&wNode);
    REQUIRE(PKB::getInstance()->isModifies("3","x"));
}

TEST_CASE("test") {

    PKB::getInstance()->setParent(5,6);
    REQUIRE(PKB::getInstance()->isParent("5","6"));
}