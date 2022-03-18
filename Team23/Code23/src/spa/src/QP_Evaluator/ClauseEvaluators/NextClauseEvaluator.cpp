//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextClauseEvaluator.h"

unordered_set<std::string> retrieveStmtSetFromMap(unordered_map<int, NodeCFG*> nextMap);

bool NextClauseEvaluator::isRelation(string left, string right) {
    return pkb->getInstance()->relationship.next.isNext(left, right);
}

unordered_set<std::string> NextClauseEvaluator::getLeftSynonymValue(std::string right) {
    return pkb->getInstance()->relationship.next.getPreviousNodeOf(right);
}

unordered_set<std::string> NextClauseEvaluator::getRightSynonymValue(std::string left) {
    return pkb->getInstance()->
            relationship.next.getNextNodeOf(left);
}

pair<DesignEntity, DesignEntity> NextClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}

unordered_set<std::string> retrieveStmtSetFromMap(unordered_map<int, NodeCFG*> nextMap) {
    unordered_set<std::string> set;
    unordered_map<int, NodeCFG*>::iterator i;
    for(i = nextMap.begin(); i != nextMap.end() ; ++i) {
        string stmtNo = to_string((*i).first);
        set.insert(stmtNo);
    }
    return set;
}