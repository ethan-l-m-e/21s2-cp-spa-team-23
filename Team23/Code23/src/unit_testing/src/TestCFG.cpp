//
// Created by Tin Hong Wen on 4/3/22.
//
#include <iostream>

#include "TNode/CFG/NodeCFG.h"

#include "catch.hpp"

TEST_CASE("Test straight Nodes") {
    NodeCFG* node1 = new NodeCFG(1);
    NodeCFG* node2 = new NodeCFG(2);
    node1->setNextNode(node2);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setNextNode(node3);
    NodeCFG* node4 = new NodeCFG(4);
    node3->setNextNode(node4);
    NodeCFG* node5 = new NodeCFG(5);
    node4->setNextNode(node5);

    CHECK(node1->isStart());
    CHECK(!node2->isStart());
    CHECK(!node2->isEnd());
    CHECK(node5->isEnd());

    CHECK(5 == node1->getEndNode()->getStatementNumber());
    CHECK(5 == node3->getEndNode()->getStatementNumber());
    CHECK(5 == node5->getEndNode()->getStatementNumber());

    CHECK(1 == node1->getStartNode()->getStatementNumber());
    CHECK(1 == node3->getStartNode()->getStatementNumber());
    CHECK(1 == node5->getStartNode()->getStatementNumber());

    CHECK(node2->getAllPreviousNode()[1] == node1);
    CHECK(node2 -> getNextNode() == node3);
    CHECK(node4->getAllPreviousNode()[3] == node3);
    CHECK(node4 -> getNextNode() == node5);
}

TEST_CASE("Branch Nodes") {
    NodeCFG* node1 = new NodeCFG(1);
    BranchCFG* node2 = new BranchCFG(2);
    node1->setNextNode(node2);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setLeftNode(node3);
    NodeCFG* node4 = new NodeCFG(4);
    node2->setRightNode(node4);
    NodeCFG* node5 = new NodeCFG(5);
    node3->setNextNode(node5);
    node4->setNextNode(node5);

    CHECK(node2->getLeftNode() == node3);
    CHECK(node2->getRightNode() == node4);
    CHECK(node5->getAllPreviousNode()[3] == node3);
    CHECK(node5->getAllPreviousNode()[4] == node4);
    CHECK(node1->getEndNode() == node5);
    CHECK(node5->getStartNode() == node1);
}

TEST_CASE("node with imaginary end") {

    NodeCFG* node1 = new NodeCFG(1);
    BranchCFG* node2 = new BranchCFG(2);
    node1->setNextNode(node2);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setLeftNode(node3);
    NodeCFG* node4 = new NodeCFG(4);
    node2->setRightNode(node4);


    CHECK(node2->getLeftNode() == node3);
    CHECK(node2->getRightNode() == node4);
    CHECK(node1->getEndNode() == node4);

}

//Imaginary Merge can happen in these cases:
//1) last statement in the procedure is an if statement
//2) last statement in a while/if statement is an if statement
TEST_CASE("nested branches with real end") {
    // 1 -< 2, 5
    // 2 -< 3, 4
    // 5 -< 6, 7
    // 8
    /*
     * if(x < y) then {
     *      if(s , c) then {
     *          dsds;
     *       } else {sdasdasd;}} else {
     *      if(s , c) then {
     *          dsds;
     *       } else {sdasdasd;     }}
     * asdasdsad;
     */

    BranchCFG* node1 = new BranchCFG(1);

    BranchCFG* node2 = new BranchCFG(2);
    node1->setLeftNode(node2);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setLeftNode(node3);
    NodeCFG* node4 = new NodeCFG(4);
    node2->setRightNode(node4);


    BranchCFG* node5 = new BranchCFG(5);
    node1->setRightNode(node5);
    NodeCFG* node6 = new NodeCFG(6);
    node5->setLeftNode(node6);
    NodeCFG* node7 = new NodeCFG(7);
    node5->setRightNode(node7);

    NodeCFG* node8 = new NodeCFG(8);
    node3->setNextNode(node8);
    node4->setNextNode(node8);
    node6->setNextNode(node8);
    node7->setNextNode(node8);


    CHECK(node1->getEndNode() == node8);
    CHECK(node8->getStartNode() == node1);
}

TEST_CASE("nexted Branch; imaginary end") {
    // 1 -< 2, 5
    // 2 -< 3, 4
    // 5 -< 6, 7
    // 8
    /*
     * if(x < y) then {
     *      if(s , c) then {
     *          dsds;
     *       } else {sdasdasd;}} else {
     *      if(s , c) then {
     *          dsds;
     *       } else {sdasdasd;     }}
     * asdasdsad;
     */

    BranchCFG* node1 = new BranchCFG(1);

    BranchCFG* node2 = new BranchCFG(2);
    node1->setLeftNode(node2);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setLeftNode(node3);
    NodeCFG* node4 = new NodeCFG(4);
    node2->setRightNode(node4);



    BranchCFG* node5 = new BranchCFG(5);
    node1->setRightNode(node5);
    NodeCFG* node6 = new NodeCFG(6);
    node5->setLeftNode(node6);
    NodeCFG* node7 = new NodeCFG(7);
    node5->setRightNode(node7);



    CHECK(node1->getEndNode() == node7);
}

TEST_CASE("Loop Nodes") {
    LoopCFG* node1 = new LoopCFG(1);
    vector<NodeCFG*>* nodeSet;
    NodeCFG* node2 = new NodeCFG(2);
    nodeSet->push_back(node2);
    node1->setNodeInLoop(nodeSet);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setNextNode(node3);
    NodeCFG* node4 = new NodeCFG(4);
    node3->setNextNode(node4);
    NodeCFG* node5 = new NodeCFG(5);
    node4->setNextNode(node5);
    node5->setNextNode(node1);

    CHECK(node1->isStart());
    CHECK(node1->isEnd());
    CHECK(node1->getNodeInLoop() == node2);
}


