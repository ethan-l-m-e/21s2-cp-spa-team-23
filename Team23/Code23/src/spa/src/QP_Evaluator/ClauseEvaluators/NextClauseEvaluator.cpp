//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextClauseEvaluator.h"

bool NextClauseEvaluator::isRelation(string left, string right) {
    //return pkb->isNext(left, right)
    return false;
}

unordered_set<std::string> NextClauseEvaluator::getLeftSynonymValue(std::string right) {
    //return pkb-getPreviousNodeOf(right);
    return {};
}

unordered_set<std::string> NextClauseEvaluator::getRightSynonymValue(std::string left) {
    //return pkb-getNextNodeOf(left);
    return {};
}

pair<DesignEntity, DesignEntity> NextClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}