//
// Created by Tianyi Wang on 10/2/22.
//

#include "FollowsTClauseEvaluator.h"

bool FollowsTClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.followsT.isRelationship(left, right);
}

unordered_set<string> FollowsTClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.followsT.getLHS(right);
}

unordered_set<string> FollowsTClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.followsT.getRHS(left);
}

pair<DesignEntity, DesignEntity> FollowsTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}