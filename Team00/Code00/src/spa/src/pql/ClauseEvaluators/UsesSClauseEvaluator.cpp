//
// Created by Tianyi Wang on 17/2/22.
//

#include "UsesSClauseEvaluator.h"

bool UsesSClauseEvaluator::isRelation(std::string left, std::string right) {
    //return pkb->isUses(left, right);
}

unordered_set<std::string> UsesSClauseEvaluator::getLeftSynonymValue(std::string right) {
    //return pkb->getUsesStmt(right);
}

unordered_set<std::string> UsesSClauseEvaluator::getRightSynonymValue(std::string left) {
    //return pkb->getUsesVar(left);
}

pair<DesignEntity, DesignEntity> UsesSClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}