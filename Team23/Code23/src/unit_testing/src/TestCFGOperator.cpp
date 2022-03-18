//
// Created by Tin Hong Wen on 11/3/22.
//

#include "QP_database/CFGOperator.h"
#include "QP_Evaluator/TestUtilities.h"
#include "catch.hpp"

using namespace std;
/*
vector<unordered_map<int, NodeCFG*>> constructCFGForTesting() {
    BranchCFG* branch1 = new BranchCFG(1);
    NodeCFG* node2 = new NodeCFG(2);
    NodeCFG* node3 = new NodeCFG(3);
    NodeCFG* node4 = new NodeCFG(4);
    NodeCFG* node5 = new NodeCFG(5);
    LoopCFG* loop6 = new LoopCFG(6);
    LoopCFG* loop7 = new LoopCFG(7);
    NodeCFG* node8 = new NodeCFG(8);
    NodeCFG* node9 = new NodeCFG(9);
    LoopCFG* loop10 = new LoopCFG(10);
    NodeCFG* node11 = new NodeCFG(11);
    BranchCFG* branch12 = new BranchCFG(12);
    NodeCFG* node13 = new NodeCFG(13);
    NodeCFG* node14 = new NodeCFG(14);

    branch1->setLeftNode(node2);
    node2->setNextNode(node3);
    node3->setNextNode(node4);
    node4->setNextNode(node5);

    branch1->setRightNode(loop6);
    loop6->setNodeInLoop(loop7);
    loop7->setNodeInLoop(node8);
    node8->setNextNode(loop7);
    loop7->setNextNode(loop6);

    node5->setNextNode(node9);
    loop6->setNextNode(node9);
    node9->setNextNode(loop10);
    loop10->setNodeInLoop(node11);
    node11->setNextNode(branch12);
    branch12->setLeftNode(node13);
    branch12->setRightNode(node14);
    node13->setNextNode(loop10);
    node14->setNextNode(loop10);

    NodeCFG* node15 = new NodeCFG(15);
    NodeCFG* node16 = new NodeCFG(16);
    NodeCFG* node17 = new NodeCFG(17);

    node15->setNextNode(node16);
    node16->setNextNode(node17);

    unordered_map<int, NodeCFG*> allNodes;
    allNodes[1] = branch1;
    allNodes[2] = node2;
    allNodes[3] = node3;
    allNodes[4] = node4;
    allNodes[5] = node5;
    allNodes[6] = loop6;
    allNodes[7] = loop7;
    allNodes[8] = node8;
    allNodes[9] = node9;
    allNodes[10] = loop10;
    allNodes[11] = node11;
    allNodes[12] = branch12;
    allNodes[13] = node13;
    allNodes[14] = node14;
    allNodes[15] = node15;
    allNodes[16] = node16;
    allNodes[17] = node17;
    unordered_map<int, NodeCFG*> rootNodes;
    return vector<unordered_map<int, NodeCFG*>>{allNodes, rootNodes};
}
*/
TEST_CASE("if path exist between 2 nodes") {
    vector<unordered_map<int, NodeCFG*>> nodeMap = constructCFGForTesting();
    unordered_map<int, NodeCFG*> allNodes = nodeMap[0];
    int size = nodeMap.size();

    //different procedure
    CFGOperator* cfgHandler = CFGOperator::getInstance();
    CHECK(!cfgHandler->pathExistBetween(allNodes[4], allNodes[16], size));
    // direct
    CHECK(cfgHandler->pathExistBetween(allNodes[1], allNodes[2], size));
    CHECK(cfgHandler->pathExistBetween(allNodes[2], allNodes[3], size));
    CHECK(cfgHandler->pathExistBetween(allNodes[1], allNodes[5], size));

    //loop
    CHECK(!cfgHandler->pathExistBetween(allNodes[3], allNodes[8], size));
    CHECK(cfgHandler->pathExistBetween(allNodes[8], allNodes[7], size));
    CHECK(cfgHandler->pathExistBetween(allNodes[8], allNodes[6], size));

    //branch
    CHECK(!cfgHandler->pathExistBetween(allNodes[4], allNodes[8], size));
    CHECK(cfgHandler->pathExistBetween(allNodes[4], allNodes[13], size));

}


TEST_CASE("all possible right Nodes") {
    vector<unordered_map<int, NodeCFG*>> nodeMap = constructCFGForTesting();
    unordered_map<int, NodeCFG*> allNodes = nodeMap[0];
    int size = nodeMap.size();
    CFGOperator* cfgHandler = CFGOperator::getInstance();
    CHECK(unordered_set<string>{} == cfgHandler->gatherAllRightNodes(allNodes[17], size));
    CHECK(unordered_set<string>{"17"} == cfgHandler->gatherAllRightNodes(allNodes[16], size));
    CHECK(unordered_set<string>{"16", "17"} == cfgHandler->gatherAllRightNodes(allNodes[15], size));
    CHECK(unordered_set<string>{"2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"} ==
                  cfgHandler->gatherAllRightNodes(allNodes[1], size));
    CHECK(unordered_set<string>{"3", "4", "5", "9", "10", "11", "12", "13", "14"} == cfgHandler->gatherAllRightNodes(allNodes[2], size));
    CHECK(unordered_set<string>{"6", "7", "8", "9", "10", "11", "12", "13", "14"} == cfgHandler->gatherAllRightNodes(allNodes[8], size));
    CHECK(unordered_set<string>{"6", "7", "8", "9", "10", "11", "12", "13", "14"} == cfgHandler->gatherAllRightNodes(allNodes[7], size));
    CHECK(unordered_set<string>{"10", "11", "12", "13", "14"} == cfgHandler->gatherAllRightNodes(allNodes[14], size));

}

TEST_CASE("all possible left Nodes") {
    vector<unordered_map<int, NodeCFG *>> nodeMap = constructCFGForTesting();
    unordered_map<int, NodeCFG *> allNodes = nodeMap[0];
    int size = nodeMap.size();
    CFGOperator* cfgHandler = CFGOperator::getInstance();
    CHECK(unordered_set<string>{} == cfgHandler->gatherAllLeftNodes(allNodes[15], size));
    CHECK(unordered_set<string>{"15"} == cfgHandler->gatherAllLeftNodes(allNodes[16], size));
    CHECK(unordered_set<string>{"15", "16"} == cfgHandler->gatherAllLeftNodes(allNodes[17], size));
    CHECK(unordered_set<string>{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"} ==
                  cfgHandler->gatherAllLeftNodes(allNodes[14], size));
    CHECK(unordered_set<string>{"1", "2", "3", "4", "5", "6", "7", "8"} == cfgHandler->gatherAllLeftNodes(allNodes[9], size));
    CHECK(unordered_set<string>{"1", "6", "7", "8"} == cfgHandler->gatherAllLeftNodes(allNodes[8], size));
}


TEST_CASE("test lambda") {
    int arg = 3;
    //bool (*function1)(int) = [](int x) { return CFGOperator::boolFoo(x); };
    //CFGOperator::testFoo(function1);
}