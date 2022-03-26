//
// Created by Tianyi Wang on 17/2/22.
//

#include "UsesSClauseEvaluator.h"

bool UsesSClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.usesS.isRelationship(left, right);
}

unordered_set<string> UsesSClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.usesS.getLHS(right);
}

unordered_set<string> UsesSClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.usesS.getRHS(left);
}

pair<DesignEntity, DesignEntity> UsesSClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}