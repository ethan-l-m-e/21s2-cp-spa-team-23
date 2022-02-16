//
// Created by Tianyi Wang on 5/2/22.
//

#include "FollowsClauseEvaluator.h"

bool FollowsClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->isFollows(stoi(left), stoi(right));
}

unordered_set<std::string> FollowsClauseEvaluator::getLeftSynonymValue(std::string right) {
    int followee = pkb->getFollowee(stoi(right));
    if (followee == -1) return {};
    return {to_string(followee)};
}

unordered_set<std::string> FollowsClauseEvaluator::getRightSynonymValue(std::string left) {
    int follower = pkb->getFollower(stoi(left));
    if (follower == -1) return {};
    return {to_string(follower)};
}

pair<DesignEntity, DesignEntity> FollowsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}



