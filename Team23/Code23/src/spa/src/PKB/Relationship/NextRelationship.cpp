//
// Created by Karan Dev Sapra on 16/3/22.
//

#include "NextRelationship.h"


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

    if (setNextNode.empty() || setNextNode.size() != 1) {
        unordered_map<int, NodeCFG *> emptyMap;
        return emptyMap;
    } else {
        NodeCFG *nextNode = *setNextNode.begin();

        return nextNode->getAllPreviousNode();
    }
}

NodeCFG* NextRelationship::getNextNodeOf(int previous) {
    unordered_set<NodeCFG *> setPreviousNode = getRHSNormal(previous);

    if (setPreviousNode.empty() || setPreviousNode.size() != 1) {
        return nullptr;
    } else {
        NodeCFG *previousNode = *setPreviousNode.begin();

        return previousNode->getNextNode();
    }
}