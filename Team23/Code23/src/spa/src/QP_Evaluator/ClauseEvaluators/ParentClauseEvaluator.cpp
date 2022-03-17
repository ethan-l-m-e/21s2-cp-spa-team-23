//
// Created by Tianyi Wang on 11/2/22.
//

#include "ParentClauseEvaluator.h"


bool ParentClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->relationship.parent.isRelationship(left, right);
}

unordered_set<std::string> ParentClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->relationship.parent.getLHS(right);
}

unordered_set<std::string> ParentClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->relationship.parent.getSetRHS(left);
}

pair<DesignEntity, DesignEntity> ParentClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}
