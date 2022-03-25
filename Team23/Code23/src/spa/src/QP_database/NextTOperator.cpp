//
// Created by Tin Hong Wen on 22/3/22.
//

#include "NextTOperator.h"

bool NextTOperator::computeRelation(string left, string right) {
    if(stmtIsNotInSource(vector<string>{left, right})) return false;
    NodeCFG* leftNode = retrieveNode(left);
    NodeCFG* rightNode = retrieveNode(right);
    int size = getSize();
    return graphMethods->DFSBoolean(leftNode,
                                    rightNode,
                                    size,
                                    graphMethods->IsReachableForward);
}

unordered_set<string> NextTOperator::computeRHS(string left) {
    if(stmtIsNotInSource(vector<string>{left})) return {};
    NodeCFG* leftNode = retrieveNode(left);
    int size = getSize();
    stmtSetNum resultSet = graphMethods->DFSResultSet(leftNode,
                                                      size,
                                                      graphMethods->collateAllAdjacentNodes,
                                                      graphMethods->searchNodesAlongPathAfter);
    return convertIntToString(resultSet);
}

unordered_set<string> NextTOperator::computeLHS(string right) {
    if(stmtIsNotInSource(vector<string>{right})) return {};
    NodeCFG* rightNode = retrieveNode(right);
    int size = getSize();
    stmtSetNum resultSet = graphMethods->DFSResultSet(rightNode,
                                                      size,
                                                      graphMethods->collateAllPreviousNodes,
                                                      graphMethods->searchNodesAlongPathBefore);
    return convertIntToString(resultSet);
}


NextTOperator *NextTOperator::singleton = nullptr;
NextTOperator::NextTOperator(): CacheOperator(){}
NextTOperator* NextTOperator::getInstance() {
    if (NextTOperator::singleton == nullptr) {
        NextTOperator::singleton = new NextTOperator();
    }
    return NextTOperator::singleton;
}