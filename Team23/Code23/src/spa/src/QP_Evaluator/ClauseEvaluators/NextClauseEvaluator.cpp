//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextClauseEvaluator.h"

unordered_set<string> retrieveStmtSetFromMap(unordered_map<int, NodeCFG*> nextMap);

bool NextClauseEvaluator::isRelation(string left, string right) {
    return pkb->relationship.next.isRelationship(left, right);
}

unordered_set<string> NextClauseEvaluator::getLeftSynonymValue(string right) {
    return pkb->relationship.next.getLHS(right);
}

unordered_set<string> NextClauseEvaluator::getRightSynonymValue(string left) {
    return pkb->relationship.next.getRHS(left);
}

pair<DesignEntity, DesignEntity> NextClauseEvaluator::getWildcardType () {
    return make_pair(DesignEntity::STMT, DesignEntity::STMT);
}

unordered_set<string> retrieveStmtSetFromMap(unordered_map<int, NodeCFG*> nextMap) {
    unordered_set<string> set;
    unordered_map<int, NodeCFG*>::iterator i;
    for(i = nextMap.begin(); i != nextMap.end() ; ++i) {
        string stmtNo = to_string((*i).first);
        set.insert(stmtNo);
    }
    return set;
}