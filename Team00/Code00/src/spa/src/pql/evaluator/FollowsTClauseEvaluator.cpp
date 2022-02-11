//
// Created by Tianyi Wang on 10/2/22.
//

#include "FollowsTClauseEvaluator.h"

bool FollowsTClauseEvaluator::isRelation(std::string left, std::string right) {
    //return pkb->isFollowsT(left, right);
    return false;
}

unordered_set<std::string> FollowsTClauseEvaluator::getLeftSynonymValue(std::string right) {
    //return pkb->getStmtFollowedTBy(right);
    return unordered_set<std::string>{};
}

unordered_set<std::string> FollowsTClauseEvaluator::getRightSynonymValue(std::string left) {
    //return pkb->getStmtFollowsT(left);
    return unordered_set<std::string>{};
}