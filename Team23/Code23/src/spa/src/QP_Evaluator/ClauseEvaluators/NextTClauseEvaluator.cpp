//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextTClauseEvaluator.h"
#include "TNode/CFG/NodeCFG.h"
#include "QP_database/CFGOperator.h"

bool NextTClauseEvaluator::isRelation(string left, string right) {
    //pkb->getCFGNode(left)
    //pkb->getCFGNode(right)
    // pkb->getCFGSize()
    //CFGOperator::pathExistBetween(leftNode, rightNode, size);
    return false;
}

unordered_set<std::string> NextTClauseEvaluator::getLeftSynonymValue(std::string right) {
    //pkb->getCFGNode(right)
    // pkb->getCFGSize()
    //CFGOperator::gatherAllLeftNodesNext(rightNode, size);
    return {};
}

unordered_set<std::string> NextTClauseEvaluator::getRightSynonymValue(std::string left) {
    // pkb->getCFGNode(left)
    // pkb->getCFGSize()
    //CFGOperator::gatherAllRightNodesNext(leftNode, size);
    return {};
}

pair<DesignEntity, DesignEntity> NextTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}