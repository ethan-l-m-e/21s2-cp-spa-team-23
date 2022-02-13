//
// Created by Tianyi Wang on 11/2/22.
//

#include "ParentClauseEvaluator.h"

bool ParentClauseEvaluator::isRelation(std::string left, std::string right) {
    //return pkb->isParent(left, right);
    return false;
}

unordered_set<std::string> ParentClauseEvaluator::getLeftSynonymValue(std::string right) {
    //return pkb->getParent(right);
    return unordered_set<std::string>{};
}

unordered_set<std::string> ParentClauseEvaluator::getRightSynonymValue(std::string left) {
    //return pkb->getChild(left);
    return unordered_set<std::string>{};
}