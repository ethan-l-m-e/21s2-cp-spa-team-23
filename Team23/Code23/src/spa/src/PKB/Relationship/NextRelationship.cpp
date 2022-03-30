//
// Created by Karan Dev Sapra on 16/3/22.
//

#include "NextRelationship.h"


void NextRelationship::clear() {
    statementNumberToCfgNodeMap.clear();
}
void NextRelationship::addCFGNode(NodeCFG *node) {
    int statementNumber = node->getStatementNumber();

    statementNumberToCfgNodeMap.emplace(std::to_string(statementNumber), node);

}

bool NextRelationship::isRelationship(string previousStatementNumber, string nextStatementNumber) {

    unordered_set<string> setPreviousStatementNumbers = getLHS(nextStatementNumber);

    return setPreviousStatementNumbers.find(previousStatementNumber) != setPreviousStatementNumbers.end();
}


unordered_set<string> NextRelationship::getLHS(string nextStatementNumber) {

    NodeCFG *node = statementNumberToCfgNodeMap[nextStatementNumber];

    unordered_set<string> statementNumbers;

    unordered_map<int, NodeCFG*> statementNumberToNodeMap = node->getAllPreviousNode();

    for (auto& iter : statementNumberToNodeMap) {
        statementNumbers.insert(std::to_string(iter.first));
    }

    return statementNumbers;


}

unordered_set<string> NextRelationship::getRHS(string previousStatementNumber) {

    NodeCFG *node = statementNumberToCfgNodeMap[previousStatementNumber];

    unordered_set<string> setNextStatementNumbers;

    if (auto branchNode = dynamic_cast<BranchCFG *>(node)) {
        NodeCFG *leftNode = branchNode->getLeftNode();
        NodeCFG *rightNode = branchNode->getRightNode();

        setNextStatementNumbers.insert(std::to_string(leftNode->getStatementNumber()));
        setNextStatementNumbers.insert(std::to_string(rightNode->getStatementNumber()));

    } else if (auto loopNode = dynamic_cast<LoopCFG *>(node)) {
        NodeCFG *nextNodeInLoop = loopNode->getNodeInLoop();
        NodeCFG *nextNode = loopNode->getNextNode();

        setNextStatementNumbers.insert(std::to_string(nextNodeInLoop->getStatementNumber()));

        if (nextNode != NULL) {
            setNextStatementNumbers.insert(std::to_string(nextNode->getStatementNumber()));
        }


    } else {
        NodeCFG *nextNode = node->getNextNode();

        if (nextNode != NULL) {
            setNextStatementNumbers.insert(std::to_string(nextNode->getStatementNumber()));
        }
    }

    return setNextStatementNumbers;

}


// Functions below are used to calculate Next*


NodeCFG* NextRelationship::getCFGNode(string statementNumber) {
    return statementNumberToCfgNodeMap[statementNumber];
}

int NextRelationship::getCFGSize() {
    return statementNumberToCfgNodeMap.size();
}


