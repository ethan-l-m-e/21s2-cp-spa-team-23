//
// Created by Tianyi Wang on 6/3/22.
//

#include "UsesPClauseEvaluator.h"

bool UsesPClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.usesP.isRelationship(left, right);
}

unordered_set<string> UsesPClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.usesP.getLHS(right);
}

unordered_set<string> UsesPClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.usesP.getRHS(left);
}

pair<DesignEntity, DesignEntity> UsesPClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}