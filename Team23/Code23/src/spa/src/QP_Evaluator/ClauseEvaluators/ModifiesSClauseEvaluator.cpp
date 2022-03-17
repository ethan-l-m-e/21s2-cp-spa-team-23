//
// Created by Tianyi Wang on 17/2/22.
//

#include "ModifiesSClauseEvaluator.h"

bool ModifiesSClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.modifiesS.isRelationship(left, right);
}

unordered_set<std::string> ModifiesSClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.modifiesS.getSetLHS(right);
}

unordered_set<std::string> ModifiesSClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.modifiesS.getSetRHS(left);
}

pair<DesignEntity, DesignEntity> ModifiesSClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}