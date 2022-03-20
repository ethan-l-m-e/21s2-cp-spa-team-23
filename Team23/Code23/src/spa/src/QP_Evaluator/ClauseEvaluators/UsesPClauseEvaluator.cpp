//
// Created by Tianyi Wang on 6/3/22.
//

#include "UsesPClauseEvaluator.h"

bool UsesPClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.usesP.isRelationship(left, right);
}

unordered_set<std::string> UsesPClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.usesP.getLHS(right);
}

unordered_set<std::string> UsesPClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.usesP.getRHS(left);
}

pair<DesignEntity, DesignEntity> UsesPClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}