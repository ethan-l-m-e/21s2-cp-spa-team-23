//
// Created by Tianyi Wang on 17/2/22.
//

#include "ModifiesSClauseEvaluator.h"

bool ModifiesSClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.modifiesS.isRelationship(left, right);
}

unordered_set<string> ModifiesSClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.modifiesS.getLHS(right);
}

unordered_set<string> ModifiesSClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.modifiesS.getRHS(left);
}

pair<DesignEntity, DesignEntity> ModifiesSClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::EMPTY, DesignEntity::VARIABLE);
}