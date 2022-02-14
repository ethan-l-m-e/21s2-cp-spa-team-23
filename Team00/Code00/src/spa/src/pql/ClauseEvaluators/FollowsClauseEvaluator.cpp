//
// Created by Tianyi Wang on 5/2/22.
//

#include "FollowsClauseEvaluator.h"

bool FollowsClauseEvaluator::isRelation(std::string left, std::string right) {
    //return pkb->isFollows(left, right);
    return false;
}

unordered_set<std::string> FollowsClauseEvaluator::getLeftSynonymValue(std::string right) {
    //return pkb->getStmtFollowedBy(right);
    return unordered_set<std::string>{};
}

unordered_set<std::string> FollowsClauseEvaluator::getRightSynonymValue(std::string left) {
    //return pkb->getStmtFollows(left);
    return unordered_set<std::string>{};
}



