//
// Created by Tianyi Wang on 17/2/22.
//

#include "ParentTClauseEvaluator.h"

bool ParentTClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->isParentT(left, right);
}

unordered_set<std::string> ParentTClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->getParentT(right);
}

unordered_set<std::string> ParentTClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->getChildrenT(left);
}

pair<DesignEntity, DesignEntity> ParentTClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}