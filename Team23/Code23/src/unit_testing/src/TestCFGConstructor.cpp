//
// Created by Lucas Tai on 13/3/22.
//
#include "iostream"
#include "TNode/TNode.h"
#include "catch.hpp"
#include "TNode/CFG/CFGConstructor.h"

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

TEST_CASE("test - basic CFG") {
    StatementList defaultStmtLst;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    vector<NodeCFG*>* firstSetOfNodes = CFGConstructor::createCFG(pNode);

    CHECK(firstSetOfNodes->at(0)->getStatementNumber() == 1);
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getStatementNumber() == 2);
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getStatementNumber() == 3);
    CHECK(firstSetOfNodes->at(0)->isStart());
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->isEnd());
}

TEST_CASE("test - basic while") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);
    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    auto wNode = WhileNode(4, condPtr, defaultStmtLst2);
    defaultStmtLst.push_back(&wNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    vector<NodeCFG*>* firstSetOfNodes = CFGConstructor::createCFG(pNode);

    CHECK(firstSetOfNodes->at(0)->getStatementNumber() == 1);
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getStatementNumber() == 2);
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getStatementNumber() == 3);
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getNextNode()->getStatementNumber()==4);
    CHECK(firstSetOfNodes->at(0)->isStart());
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getNextNode()->isEnd());
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getNextNode()));
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getNextNode())->getNodeInLoop()->getStatementNumber() == 5);
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getNextNode())->getNodeInLoop()->getNextNode()->getStatementNumber() == 6);
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes->at(0)->getNextNode()->getNextNode()->getNextNode())->getNodeInLoop()->getNextNode()->getNextNode()->getStatementNumber() == 4);

}
TEST_CASE("test - basic if") {

    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst3.push_back(&cNode);

    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    IfNode iNode = IfNode(2, condPtr, defaultStmtLst3, defaultStmtLst2);

    defaultStmtLst.push_back(&iNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    vector<NodeCFG*>* firstSetOfNodes = CFGConstructor::createCFG(pNode);
    CHECK(firstSetOfNodes->at(0)->getStatementNumber() == 1);
    CHECK(firstSetOfNodes->at(0)->getNextNode()->getStatementNumber() == 2);
    CHECK(firstSetOfNodes->at(0)->isStart());
    CHECK(firstSetOfNodes->at(0)->getNextNode()->isEnd()==false);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes->at(0)->getNextNode()));
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes->at(0)->getNextNode())->getLeftNode()->getStatementNumber()==3);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes->at(0)->getNextNode())->getLeftNode()->isEnd());
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes->at(0)->getNextNode())->getRightNode()->getStatementNumber()==5);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes->at(0)->getNextNode())->getRightNode()->getNextNode()->getStatementNumber()==6);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes->at(0)->getNextNode())->getRightNode()->getNextNode()->isEnd());

}