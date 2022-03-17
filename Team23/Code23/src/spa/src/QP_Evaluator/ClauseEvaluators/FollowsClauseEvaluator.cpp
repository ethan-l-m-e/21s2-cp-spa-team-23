//
// Created by Tianyi Wang on 5/2/22.
//

#include "FollowsClauseEvaluator.h"

bool FollowsClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.follows.isRelationship(left, right);
}

unordered_set<std::string> FollowsClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.follows.getLHS(right);
}

unordered_set<std::string> FollowsClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.follows.getRHS(left);
}

pair<DesignEntity, DesignEntity> FollowsClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}



