//
// Created by Tianyi Wang on 17/2/22.
//

#include "ParentTClauseEvaluator.h"

bool ParentTClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.parentT.isRelationship(left, right);
}

unordered_set<string> ParentTClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.parentT.getLHS(right);
}

unordered_set<string> ParentTClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.parentT.getRHS(left);
}

pair<DesignEntity, DesignEntity> ParentTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}