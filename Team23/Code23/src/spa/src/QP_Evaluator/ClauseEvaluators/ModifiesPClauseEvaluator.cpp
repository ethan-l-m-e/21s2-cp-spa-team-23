//
// Created by Tianyi Wang on 6/3/22.
//

#include "ModifiesPClauseEvaluator.h"

bool ModifiesPClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.modifiesP.isRelationship(left, right);
}

unordered_set<std::string> ModifiesPClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.modifiesP.getLHS(right);
}

unordered_set<std::string> ModifiesPClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.modifiesP.getRHS(left);
}

pair<DesignEntity, DesignEntity> ModifiesPClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}