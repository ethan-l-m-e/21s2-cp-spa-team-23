//
// Created by Tianyi Wang on 17/2/22.
//

#include "ParentTClauseEvaluator.h"

bool ParentTClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.parentT.isRelationship(left, right);
}

unordered_set<std::string> ParentTClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.parentT.getSetLHS(right);
}

unordered_set<std::string> ParentTClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.parentT.getSetRHS(left);
}

pair<DesignEntity, DesignEntity> ParentTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}