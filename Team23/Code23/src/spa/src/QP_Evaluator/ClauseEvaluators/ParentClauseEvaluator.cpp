//
// Created by Tianyi Wang on 11/2/22.
//

#include "ParentClauseEvaluator.h"


bool ParentClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.parent.isRelationship(left, right);
}

unordered_set<string> ParentClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.parent.getLHS(right);
}

unordered_set<string> ParentClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.parent.getRHS(left);
}

pair<DesignEntity, DesignEntity> ParentClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}
