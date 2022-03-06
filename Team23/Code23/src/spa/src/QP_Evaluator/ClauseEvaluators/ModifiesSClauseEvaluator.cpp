//
// Created by Tianyi Wang on 17/2/22.
//

#include "ModifiesSClauseEvaluator.h"

bool ModifiesSClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->isModifiesS(left, right);
}

unordered_set<std::string> ModifiesSClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->getModifierStatements(right);
}

unordered_set<std::string> ModifiesSClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->getVariablesModifiedS(left);
}

pair<DesignEntity, DesignEntity> ModifiesSClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}