//
// Created by Tianyi Wang on 5/2/22.
//

#include "FollowsClauseEvaluator.h"

bool FollowsClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->isFollows(left, right);
}

unordered_set<std::string> FollowsClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->getFollowee(right);
}

unordered_set<std::string> FollowsClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->getFollower(left);
}

pair<DesignEntity, DesignEntity> FollowsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}



