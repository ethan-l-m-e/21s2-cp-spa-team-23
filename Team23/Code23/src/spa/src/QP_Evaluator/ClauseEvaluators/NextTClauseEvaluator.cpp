//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextTClauseEvaluator.h"
#include "TNode/CFG/NodeCFG.h"
#include "QP_database/CFGOperator.h"

bool NextTClauseEvaluator::isRelation(string left, string right) {
    NodeCFG* leftNode = pkb->relationship.next.getCFGNode(left);
    NodeCFG* rightNode = pkb->relationship.next.getCFGNode(right);
    int size = pkb->relationship.next.getCFGSize();
    return CFGOperator::getInstance()->pathExistBetween(leftNode, rightNode, size);
}

unordered_set<std::string> NextTClauseEvaluator::getLeftSynonymValue(std::string right) {
    NodeCFG* rightNode = pkb->relationship.next.getCFGNode(right);
    int size = pkb->relationship.next.getCFGSize();
    return CFGOperator::getInstance()->gatherAllLeftNodes(rightNode, size);
}

unordered_set<std::string> NextTClauseEvaluator::getRightSynonymValue(std::string left) {
    NodeCFG* leftNode = pkb->relationship.next.getCFGNode(left);
    int size = pkb->relationship.next.getCFGSize();
    return CFGOperator::getInstance()->gatherAllRightNodes(leftNode, size);
}

pair<DesignEntity, DesignEntity> NextTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}