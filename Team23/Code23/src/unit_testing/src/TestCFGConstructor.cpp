//
// Created by Lucas Tai on 13/3/22.
//
#include "iostream"
#include "TNode/TNode.h"
#include "catch.hpp"
#include "TNode/CFG/CFGConstructor.h"

using namespace std;
VariableNode v11 = VariableNode("y");
VariableNode v21 = VariableNode("x");
VariableNode v31 = VariableNode("a");
VariableNode v41 = VariableNode("b");
RelExprNode relNode1 = RelExprNode(&v21,&v11,"<");
RelExprNode* relPtr1 = &relNode1;
CondExprNode defaultCond1 = CondExprNode(relPtr1);
CondExprNode* condPtr1 = &defaultCond1;

auto aNode1= AssignNode(1,&v21,&v11);
auto bNode1= AssignNode(2,&v31,&v41);
auto cNode1= AssignNode(3,&v11,&v41);
auto dNode1= AssignNode(5,&v21,&v31);
auto eNode1= AssignNode(6,&v41,&v11);

TEST_CASE("test - basic CFG") {
    ProcNameNode p1 = ProcNameNode("test");

    StatementList defaultStmtLst;

    defaultStmtLst.push_back(&aNode1);
    defaultStmtLst.push_back(&bNode1);
    defaultStmtLst.push_back(&cNode1);

    ProcedureNode pNode1 = ProcedureNode(&p1, defaultStmtLst);

    vector<NodeCFG*> firstSetOfNodes = CFGConstructor::createCFG(&pNode1);
    CHECK(firstSetOfNodes.at(0)->getStatementNumber() == 1);
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getStatementNumber() == 2);
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getStatementNumber() == 3);
    CHECK(firstSetOfNodes.at(0)->isStart());
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->isEnd());
}

TEST_CASE("test - basic while") {
    ProcNameNode p1 = ProcNameNode("test");
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode1);
    defaultStmtLst.push_back(&bNode1);
    defaultStmtLst.push_back(&cNode1);
    defaultStmtLst2.push_back(&dNode1);
    defaultStmtLst2.push_back(&eNode1);

    auto wNode = WhileNode(4, condPtr1, defaultStmtLst2);
    defaultStmtLst.push_back(&wNode);

    ProcedureNode pNode1 = ProcedureNode(&p1, defaultStmtLst);

    vector<NodeCFG*> firstSetOfNodes = CFGConstructor::createCFG(&pNode1);
    CHECK(firstSetOfNodes.at(0)->getStatementNumber() == 1);
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getStatementNumber() == 2);
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getStatementNumber() == 3);
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getNextNode()->getStatementNumber()==4);
    CHECK(firstSetOfNodes.at(0)->isStart());
    //check how isEnd() should work with while loop
//    CHECK(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getNextNode()->isEnd());
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getNextNode()));
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getNextNode())->getNodeInLoop()->getStatementNumber() == 5);
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getNextNode())->getNodeInLoop()->getNextNode()->getStatementNumber() == 6);
    CHECK(dynamic_cast<LoopCFG*>(firstSetOfNodes.at(0)->getNextNode()->getNextNode()->getNextNode())->getNodeInLoop()->getNextNode()->getNextNode()->getStatementNumber() == 4);

}
TEST_CASE("test - basic if") {
    ProcNameNode p1 = ProcNameNode("test");

    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;

    defaultStmtLst.push_back(&aNode1);
    defaultStmtLst3.push_back(&cNode1);

    defaultStmtLst2.push_back(&dNode1);
    defaultStmtLst2.push_back(&eNode1);

    IfNode iNode = IfNode(2, condPtr1, defaultStmtLst3, defaultStmtLst2);

    defaultStmtLst.push_back(&iNode);

    ProcedureNode pNode1 = ProcedureNode(&p1, defaultStmtLst);
    vector<NodeCFG*> firstSetOfNodes = CFGConstructor::createCFG(&pNode1);
    CHECK(firstSetOfNodes.at(0)->getStatementNumber() == 1);
    CHECK(firstSetOfNodes.at(0)->getNextNode()->getStatementNumber() == 2);
    CHECK(firstSetOfNodes.at(0)->isStart());
    CHECK(firstSetOfNodes.at(0)->getNextNode()->isEnd()==false);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes.at(0)->getNextNode()));
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes.at(0)->getNextNode())->getLeftNode()->getStatementNumber()==3);
    //check how isEnd() should work with if branch
//    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes.at(0)->getNextNode())->getLeftNode()->isEnd());
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes.at(0)->getNextNode())->getRightNode()->getStatementNumber()==5);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes.at(0)->getNextNode())->getRightNode()->getNextNode()->getStatementNumber()==6);
    CHECK(dynamic_cast<BranchCFG*>(firstSetOfNodes.at(0)->getNextNode())->getRightNode()->getNextNode()->isEnd());

}

TEST_CASE("test - nested while/if-then") {
    ProcNameNode p1 = ProcNameNode("test");
    StatementList defaultStmtLst;
    StatementList defaultStmtLst1;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;

    defaultStmtLst1.push_back(&aNode1);
    defaultStmtLst2.push_back(&bNode1);
    defaultStmtLst2.push_back(&cNode1);
    defaultStmtLst3.push_back(&dNode1);
    defaultStmtLst3.push_back(&eNode1);

    IfNode iNode = IfNode(4, condPtr1, defaultStmtLst3, defaultStmtLst2);
    defaultStmtLst1.push_back(&iNode);

    auto wNode = WhileNode(0, condPtr1, defaultStmtLst1);
    defaultStmtLst.push_back(&wNode);

    ProcedureNode pNode1 = ProcedureNode(&p1, defaultStmtLst);

    vector<NodeCFG*> firstSetOfNodes = CFGConstructor::createCFG(&pNode1);
    NodeCFG* firstNode = firstSetOfNodes.at(6);
    CHECK(firstNode->getStatementNumber()==0);
    CHECK(dynamic_cast<LoopCFG*>(firstNode));
    CHECK(firstNode->getStatementNumber() == 0);
    CHECK(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getStatementNumber() == 1);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode()));
    CHECK(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode()->getStatementNumber() == 4);

    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getRightNode()->getStatementNumber() ==2);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getRightNode()->getNextNode()->getStatementNumber() ==3);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getRightNode()->getNextNode()->getNextNode()->getStatementNumber() == 0);
    CHECK(dynamic_cast<LoopCFG*>(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getRightNode()->getNextNode()->getNextNode())->getStatementNumber() == 0);

    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getLeftNode()->getStatementNumber() ==5);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getLeftNode()->getNextNode()->getStatementNumber() ==6);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getLeftNode()->getNextNode()->getNextNode()->getStatementNumber() == 0);
    CHECK(dynamic_cast<LoopCFG*>(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getNextNode())->getLeftNode()->getNextNode()->getNextNode())->getStatementNumber() == 0);

}

TEST_CASE("test - doubly nested while/if-then") {
    ProcNameNode p1 = ProcNameNode("test");
    StatementList defaultStmtLst;
    StatementList defaultStmtLst1;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;
    StatementList defaultStmtLst4;
    StatementList defaultStmtLst5;
    StatementList defaultStmtLst6;

    defaultStmtLst5.push_back(&cNode1);
    defaultStmtLst2.push_back(&dNode1);
    defaultStmtLst3.push_back(&eNode1);

    IfNode iNode1 = IfNode(4, condPtr1, defaultStmtLst2, defaultStmtLst3);
    defaultStmtLst1.push_back(&iNode1);

    auto wNode1 = WhileNode(2, condPtr1, defaultStmtLst1);
    defaultStmtLst4.push_back(&wNode1);

    IfNode iNode2 = IfNode(1, condPtr1, defaultStmtLst4, defaultStmtLst5);
    defaultStmtLst6.push_back(&iNode2);

    auto wNode2 = WhileNode(0, condPtr1, defaultStmtLst6);
    defaultStmtLst.push_back(&wNode2);

    ProcedureNode pNode1 = ProcedureNode(&p1, defaultStmtLst);

    vector<NodeCFG*> firstSetOfNodes = CFGConstructor::createCFG(&pNode1);
    NodeCFG* firstNode = firstSetOfNodes.at(6);
    CHECK(firstNode->getStatementNumber()==0);
    CHECK(dynamic_cast<LoopCFG*>(firstNode));
    CHECK(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()->getStatementNumber() == 1);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop()));

    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop())->getLeftNode()->getStatementNumber() ==2);
    CHECK(dynamic_cast<LoopCFG*>(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop())->getLeftNode()));
    CHECK(dynamic_cast<LoopCFG*>(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop())->getLeftNode())->getNodeInLoop()->getStatementNumber() == 4);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop())->getLeftNode())->getNodeInLoop())->getLeftNode()->getStatementNumber() == 5);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(dynamic_cast<BranchCFG*>(dynamic_cast<LoopCFG*>(firstNode)->getNodeInLoop())->getLeftNode())->getNodeInLoop())->getRightNode()->getStatementNumber() == 6);

}

TEST_CASE("test - doubly nested if-then") {
    ProcNameNode p1 = ProcNameNode("test");
    StatementList defaultStmtLst;
    StatementList defaultStmtLst1;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;
    StatementList defaultStmtLst4;
    StatementList defaultStmtLst5;
    StatementList defaultStmtLst6;

    defaultStmtLst3.push_back(&bNode1);
    defaultStmtLst4.push_back(&cNode1);
    defaultStmtLst5.push_back(&dNode1);
    defaultStmtLst6.push_back(&eNode1);

    IfNode iNode1 = IfNode(4, condPtr1, defaultStmtLst5, defaultStmtLst6);
    defaultStmtLst2.push_back(&iNode1);

    IfNode iNode2 = IfNode(1, condPtr1, defaultStmtLst3, defaultStmtLst4);
    defaultStmtLst1.push_back(&iNode2);

    IfNode iNode3 = IfNode(0, condPtr1, defaultStmtLst1, defaultStmtLst2);
    defaultStmtLst.push_back(&iNode3);


    ProcedureNode pNode1 = ProcedureNode(&p1, defaultStmtLst);

    vector<NodeCFG*> firstSetOfNodes = CFGConstructor::createCFG(&pNode1);
    NodeCFG* firstNode = firstSetOfNodes.at(6);
    CHECK(firstNode->getStatementNumber()==0);
    CHECK(dynamic_cast<BranchCFG*>(firstNode));
    CHECK(dynamic_cast<BranchCFG*>(firstNode)->getLeftNode()->getStatementNumber()==1);
    CHECK(dynamic_cast<BranchCFG*>(firstNode)->getRightNode()->getStatementNumber()==4);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<BranchCFG*>(firstNode)->getLeftNode()));
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<BranchCFG*>(firstNode)->getRightNode()));
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<BranchCFG*>(firstNode)->getLeftNode())->getLeftNode()->getStatementNumber()==2);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<BranchCFG*>(firstNode)->getLeftNode())->getRightNode()->getStatementNumber()==3);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<BranchCFG*>(firstNode)->getRightNode())->getLeftNode()->getStatementNumber()==5);
    CHECK(dynamic_cast<BranchCFG*>(dynamic_cast<BranchCFG*>(firstNode)->getRightNode())->getRightNode()->getStatementNumber()==6);

}