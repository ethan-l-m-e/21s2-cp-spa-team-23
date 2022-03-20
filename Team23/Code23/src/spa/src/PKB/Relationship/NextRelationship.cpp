//
// Created by Karan Dev Sapra on 16/3/22.
//

#include "NextRelationship.h"


void NextRelationship::clear() {
    OneToOneRelationship<int, NodeCFG *>::clear();
}
void NextRelationship::addCFGNode(NodeCFG *node) {
    int statementNumber = node->getStatementNumber();

    OneToOneRelationship<int, NodeCFG *>::setRelationship(statementNumber, node);
}

bool NextRelationship::isRelationship(string previousStatementNumber, string nextStatementNumber) {

    unordered_set<string> setPreviousStatementNumbers = getLHS(nextStatementNumber);

    return setPreviousStatementNumbers.find(previousStatementNumber) != setPreviousStatementNumbers.end();
}


unordered_set<string> NextRelationship::getLHS(string nextStatementNumber) {
    NodeCFG *node = *getRHSNormal(std::stoi(nextStatementNumber)).begin();

    unordered_set<string> statementNumbers;

    unordered_map<int, NodeCFG*> statementNumberToNodeMap = node->getAllPreviousNode();

    for (auto& iter : statementNumberToNodeMap) {
        statementNumbers.insert(std::to_string(iter.first));
    }

    return statementNumbers;


}

unordered_set<string> NextRelationship::getRHS(string previousStatementNumber) {
    NodeCFG *node = *getRHSNormal(std::stoi(previousStatementNumber)).begin();

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
    unordered_set<NodeCFG *> setRHS = getRHSNormal(std::stoi(statementNumber));

    return *setRHS.begin();

}

int NextRelationship::getCFGSize() {
    return getSize();
}


