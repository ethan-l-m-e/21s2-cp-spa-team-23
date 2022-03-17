//
// Created by Karan Dev Sapra on 16/3/22.
//

#include "NextRelationship.h"


void NextRelationship::clear() {
    OneToOneRelationship<int, NodeCFG *>::clear();
}

void NextRelationship::setRelationship(int lhs, NodeCFG *rhs) {
    OneToOneRelationship<int, NodeCFG *>::setRelationship(lhs, rhs);
}

bool NextRelationship::isNext(int previous, int next) {
    unordered_set<NodeCFG *> setPreviousNode = getRHSNormal(previous);
    unordered_set<NodeCFG *> setNextNode = getRHSNormal(next);

    if (setPreviousNode.size() != 1 || setNextNode.size() != 1) {
        return false;
    } else {
        NodeCFG *leftNode = *setPreviousNode.begin();
        NodeCFG *rightNode = *setNextNode.begin();

        if (rightNode->getStatementNumber() - leftNode->getStatementNumber() == 1) {
            return true;
        } else {
            return false;
        }
    }
}


unordered_map<int, NodeCFG*> NextRelationship::getPreviousNodeOf(int next) {
    unordered_set<NodeCFG *> setNextNode = getRHSNormal(next);

    NodeCFG *nextNode = *setNextNode.begin();

    return nextNode->getAllPreviousNode();

}

NodeCFG* NextRelationship::getNextNodeOf(int previous) {
    unordered_set<NodeCFG *> setPreviousNode = getRHSNormal(previous);

    NodeCFG *previousNode = *setPreviousNode.begin();

    return previousNode->getNextNode();

}


// Functions below are used to calculate Next*


NodeCFG* NextRelationship::getCFGNode(int statementNumber) {
    unordered_set<NodeCFG *> setRHS = getRHSNormal(statementNumber);

    return *setRHS.begin();

}

int NextRelationship::getCFGSize() {
    return getSize();
}


