//
// Created by Tianyi Wang on 11/2/22.
//

#include "ParentClauseEvaluator.h"

bool ParentClauseEvaluator::isRelation(std::string left, std::string right) {
    return pkb->isParent(stoi(left), stoi(right));
}

unordered_set<std::string> ParentClauseEvaluator::getLeftSynonymValue(std::string right) {
    int parent = pkb->getParent(stoi(right));
    if (parent == -1) return {};
    return {to_string(parent)};
}

unordered_set<std::string> ParentClauseEvaluator::getRightSynonymValue(std::string left) {
    unordered_set<std::string> childrenSet;
    unordered_set<int> children = pkb->getChildren(stoi(left));
    for(int child : children) {
        childrenSet.emplace(to_string(child));
    }
    return childrenSet;
}

pair<DesignEntity, DesignEntity> ParentClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}