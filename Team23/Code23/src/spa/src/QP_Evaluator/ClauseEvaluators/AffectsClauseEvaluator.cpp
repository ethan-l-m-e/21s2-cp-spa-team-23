//
// Created by Tin Hong Wen on 16/3/22.
//

#include "AffectsClauseEvaluator.h"
#include "TNode/CFG/NodeCFG.h"
#include "QP_database/AffectsOperator.h"

bool AffectsClauseEvaluator::isRelation(string left, string right) {
    NodeCFG* leftNode = pkb->relationship.next.getCFGNode(stoi(left));
    NodeCFG* rightNode = pkb->relationship.next.getCFGNode(stoi(right));
    int size = pkb->relationship.next.getCFGSize();

    AffectsOperator::getInstance()->pathExistBetween(leftNode, rightNode, size);
    return false;
}