//
// Created by Tin Hong Wen on 22/3/22.
//

#ifndef SPA_CACHECLAUSEEVALUATOR_H
#define SPA_CACHECLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

class CacheClauseEvaluator: public SuchThatClauseEvaluator {
public:
    CacheClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {
        //nextTOperator = NextTOperator::getInstance();
    }
protected:
    //NextTOperator* nextTOperator;
    // to insert cache class

};


#endif //SPA_CACHECLAUSEEVALUATOR_H
