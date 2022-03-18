//
// Created by Tin Hong Wen on 10/3/22.
//

#include "NextClauseEvaluator.h"

unordered_set<std::string> retrieveStmtSetFromMap(unordered_map<int, NodeCFG*> nextMap);

bool NextClauseEvaluator::isRelation(string left, string right) {
    return pkb->getInstance()->relationship.next.isNext(stoi(left), stoi(right));
}

unordered_set<std::string> NextClauseEvaluator::getLeftSynonymValue(std::string right) {
    unordered_map<int, NodeCFG*> allPreviousNodes= pkb->getInstance()->
            relationship.next.getPreviousNodeOf(stoi(right));
    return retrieveStmtSetFromMap(allPreviousNodes);
}

unordered_set<std::string> NextClauseEvaluator::getRightSynonymValue(std::string left) {
    int nextNode= pkb->getInstance()->
            relationship.next.getNextNodeOf(stoi(left));
    return unordered_set<std::string>{to_string(nextNode)};
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