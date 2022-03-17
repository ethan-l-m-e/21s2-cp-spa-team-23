//
// Created by Tianyi Wang on 17/2/22.
//

#include "UsesSClauseEvaluator.h"

bool UsesSClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.usesS.isRelationship(left, right);
}

unordered_set<std::string> UsesSClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.usesS.getSetLHS(right);
}

unordered_set<std::string> UsesSClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.usesS.getSetRHS(left);
}

pair<DesignEntity, DesignEntity> UsesSClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}