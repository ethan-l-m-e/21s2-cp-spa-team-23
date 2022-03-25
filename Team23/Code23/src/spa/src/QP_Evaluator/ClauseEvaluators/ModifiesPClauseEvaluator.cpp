//
// Created by Tianyi Wang on 6/3/22.
//

#include "ModifiesPClauseEvaluator.h"

bool ModifiesPClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.modifiesP.isRelationship(left, right);
}

unordered_set<string> ModifiesPClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.modifiesP.getLHS(right);
}

unordered_set<string> ModifiesPClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.modifiesP.getRHS(left);
}

pair<DesignEntity, DesignEntity> ModifiesPClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}