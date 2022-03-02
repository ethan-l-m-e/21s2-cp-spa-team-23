//
// Created by Tin Hong Wen on 5/2/22.
//
#include "iostream"
#include "SourceProcessor/RelationshipExtractor.h"
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
TEST_CASE("test follows - basic - if/else") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    IfNode iNode = IfNode(0,condPtr,defaultStmtLst,defaultStmtLst2);
    RelationshipExtractor::extractFollows(&iNode);
    REQUIRE(PKB::getInstance()->isFollows("1","2"));
    REQUIRE(PKB::getInstance()->isFollows("2","3"));
    REQUIRE(PKB::getInstance()->isFollows("3","5")==false);
    REQUIRE(PKB::getInstance()->isFollows("5","6"));
    REQUIRE(PKB::getInstance()->isFollows("2","1")==false);
    REQUIRE(PKB::getInstance()->isFollows("3","2")==false);
    REQUIRE(PKB::getInstance()->isFollows("5","3")==false);
    REQUIRE(PKB::getInstance()->isFollows("6","5")==false);
    REQUIRE(PKB::getInstance()->isFollows("1","3")==false);
    REQUIRE(PKB::getInstance()->isFollows("1","4")==false);

}
TEST_CASE("test follows - nested") {
    auto aaNode= AssignNode(1,&v2,&v1);
    auto abNode= AssignNode(2,&v3,&v4);
    auto acNode= AssignNode(4,&v1,&v4);
    auto adNode= AssignNode(5,&v2,&v3);
    auto aeNode= AssignNode(7,&v4,&v1);

    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;

    defaultStmtLst.push_back(&aaNode);
    defaultStmtLst.push_back(&abNode);

    defaultStmtLst2.push_back(&acNode);
    defaultStmtLst2.push_back(&adNode);

    defaultStmtLst3.push_back(&aeNode);

    WhileNode w2Node = WhileNode(6, condPtr, defaultStmtLst3);
    defaultStmtLst2.push_back(&w2Node);
    WhileNode w1Node = WhileNode(3, condPtr, defaultStmtLst2);
    defaultStmtLst.push_back(&w1Node);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->isFollows("1","2"));
    REQUIRE(PKB::getInstance()->isFollows("2","1")==false);
    REQUIRE(PKB::getInstance()->isFollows("2","3"));
    REQUIRE(PKB::getInstance()->isFollows("4","5"));
    REQUIRE(PKB::getInstance()->isFollows("6","5")==false);
    REQUIRE(PKB::getInstance()->isFollows("5","6"));
    REQUIRE(PKB::getInstance()->isFollows("7","6")==false);
    REQUIRE(PKB::getInstance()->isFollows("6","7")==false);
    REQUIRE(PKB::getInstance()->isFollows("4","3")==false);
    REQUIRE(PKB::getInstance()->isFollows("3","4")==false);
    REQUIRE(PKB::getInstance()->isFollows("3","5")==false);
    REQUIRE(PKB::getInstance()->isFollows("3","6")==false);
    REQUIRE(PKB::getInstance()->isFollows("3","7")==false);
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

TEST_CASE("test parents - basic while") {
    StatementList defaultStmtLst;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&wNode);
    RelationshipExtractor::extractParent(&wNode,v);
    unordered_set<string> mySet = PKB::getInstance()->getParent("2");
    for (const auto& elem: mySet) {
        /* ... process elem ... */
        cout<<elem;
        cout<<"\n";
    }
    REQUIRE(PKB::getInstance()->isParent("0","2"));
    REQUIRE(PKB::getInstance()->isParent("1","1"));
}
TEST_CASE("test parents - basic if") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    IfNode iNode = IfNode(0,condPtr,defaultStmtLst,defaultStmtLst2);
    vector<StmtLstNode*> v;
    RelationshipExtractor::extractParent(&iNode,v);
    unordered_set<string> mySet = PKB::getInstance()->getParent("2");
    for (const auto& elem: mySet) {
        /* ... process elem ... */
        cout<<elem;
        cout<<"\n";
    }
    REQUIRE(PKB::getInstance()->isParent("0","2"));
    REQUIRE(PKB::getInstance()->isParent("0","5"));
}

TEST_CASE("test parents - fail") {
    StatementList defaultStmtLst;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&wNode);
    RelationshipExtractor::extractParent(&wNode,v);
    REQUIRE(PKB::getInstance()->isParent("1","2")==false);
}

TEST_CASE("test parents* - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
//    defaultStmtLst.push_back(&cNode);

//    StatementList nestedStatementList;
//    nestedStatementList.push_back(&aNode);
//    nestedStatementList.push_back(&bNode);
    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    WhileNode w1Node = WhileNode(3, condPtr, defaultStmtLst2);
    defaultStmtLst.push_back(&w1Node);
    WhileNode w2Node = WhileNode(0, condPtr, defaultStmtLst);

    vector<StmtLstNode*> v;
    RelationshipExtractor::extractParent(&w2Node,v);
    REQUIRE(PKB::getInstance()->isParentT("0","6"));
    REQUIRE(PKB::getInstance()->isParentT("0","5"));
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