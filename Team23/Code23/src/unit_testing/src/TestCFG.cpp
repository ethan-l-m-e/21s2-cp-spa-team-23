//
// Created by Tin Hong Wen on 4/3/22.
//

#include "TNode/CFG/NodeCFG.h"

#include "catch.hpp"

TEST_CASE("Test straight Nodes") {
    NodeCFG* node1 = new NodeCFG(1);
    NodeCFG* node2 = new NodeCFG(2);
    node1->setNextNode(node2);
    node2->setPreviousNode(node1);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setNextNode(node3);
    node3->setPreviousNode(node2);
    NodeCFG* node4 = new NodeCFG(4);
    node3->setNextNode(node4);
    node4->setPreviousNode(node3);
    NodeCFG* node5 = new NodeCFG(5);
    node4->setNextNode(node5);
    node5->setPreviousNode(node4);

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

    CHECK(node2 -> getPreviousNode() == node1);
    CHECK(node2 -> getNextNode() == node3);
    CHECK(node4 -> getPreviousNode() == node3);
    CHECK(node4 -> getNextNode() == node5);
}

TEST_CASE("Branch/Merge Nodes") {
    NodeCFG* node1 = new NodeCFG(1);
    BranchCFG* node2 = new BranchCFG(2);
    node1->setNextNode(node2);
    node2->setPreviousNode(node1);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setLeftNode(node3);
    node3->setPreviousNode(node2);
    NodeCFG* node4 = new NodeCFG(4);
    node2->setRightNode(node4);
    node4->setPreviousNode(node2);
    MergeCFG* node5 = new MergeCFG(5);
    node3->setNextNode(node5);
    node4->setNextNode(node5);
    node5->setLeftPreviousNode(node3);
    node5->setRightPreviousNode(node4);

    CHECK(node2->getLeftNode() == node3);
    CHECK(node2->getRightNode() == node4);
    CHECK(node5->getLeftPreviousNode() == node3);
    CHECK(node5->getRightPreviousNode() == node4);
    CHECK(node1->getEndNode() == node5);
    CHECK(node5->getStartNode() == node1);
}

TEST_CASE("Imaginary Merge Nodes") {
    NodeCFG* node1 = new NodeCFG(1);
    BranchCFG* node2 = new BranchCFG(2);
    node1->setNextNode(node2);
    node2->setPreviousNode(node1);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setLeftNode(node3);
    node3->setPreviousNode(node2);
    NodeCFG* node4 = new NodeCFG(4);
    node2->setRightNode(node4);
    node4->setPreviousNode(node2);
    MergeCFG* node5 = new ImagineMergeCFG();
    node3->setNextNode(node5);
    node4->setNextNode(node5);
    node5->setLeftPreviousNode(node3);
    node5->setRightPreviousNode(node4);

    CHECK(node2->getLeftNode() == node3);
    CHECK(node2->getRightNode() == node4);
    CHECK(node5->getEndNode() == node4);
    CHECK(node1->getEndNode() == node4);
}

TEST_CASE("Loop Nodes") {
    LoopCFG* node1 = new LoopCFG(1);
    NodeCFG* node2 = new NodeCFG(2);
    node1->setNodeInLoop(node2);
    node2->setPreviousNode(node1);
    NodeCFG* node3 = new NodeCFG(3);
    node2->setNextNode(node3);
    node3->setPreviousNode(node2);
    NodeCFG* node4 = new NodeCFG(4);
    node3->setNextNode(node4);
    node4->setPreviousNode(node3);
    NodeCFG* node5 = new NodeCFG(5);
    node4->setNextNode(node5);
    node5->setPreviousNode(node4);
    node5->setNextNode(node1);

    CHECK(node1->isStart());
    CHECK(node1->isEnd());
    CHECK(node1->getNodeInLoop() == node2);
}


