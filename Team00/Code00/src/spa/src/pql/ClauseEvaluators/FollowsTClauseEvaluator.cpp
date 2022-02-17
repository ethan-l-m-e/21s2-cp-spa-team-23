//
// Created by Tianyi Wang on 10/2/22.
//

#include "FollowsTClauseEvaluator.h"

bool FollowsTClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->isFollowsT(left, right);
}

unordered_set<std::string> FollowsTClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->getFolloweeT(right);
}

unordered_set<std::string> FollowsTClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->getFollowerT(left);
}

pair<DesignEntity, DesignEntity> FollowsTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}