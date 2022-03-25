//
// Created by Tin Hong Wen on 11/3/22.
//

#include "QP_database/ExecutionPathServices.h"
#include "QP_Evaluator/TestUtilities.h"
#include "catch.hpp"

using namespace std;



TEST_CASE("path exist between 2 nodes") {
    PKB* pkb = constructPKBForAffectsClause();

}



/*
TEST_CASE("if path exist between 2 nodes") {
    vector<unordered_map<int, NodeCFG*>> nodeMap = constructCFGForTesting();
    unordered_map<int, NodeCFG*> allNodes = nodeMap[0];
    int size = nodeMap.size();

    //different procedure
    ExecutionPathServices* cfgHandler = ExecutionPathServices::getInstance();
    CHECK();

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
    ExecutionPathServices* cfgHandler = ExecutionPathServices::getInstance();
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
    ExecutionPathServices* cfgHandler = ExecutionPathServices::getInstance();
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
    //bool (*function1)(int) = [](int x) { return ExecutionPathServices::boolFoo(x); };
    //ExecutionPathServices::testFoo(function1);
}
*/