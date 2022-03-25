//
// Created by Tin Hong Wen on 22/3/22.
//

#ifndef SPA_CACHECLAUSEEVALUATOR_H
#define SPA_CACHECLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"

class CacheClauseEvaluator: public SuchThatClauseEvaluator {
public:
    CacheClauseEvaluator (vector<Argument> args, PKB* pkb, Query* query) : SuchThatClauseEvaluator(std::move(args), pkb, query) {
        //nextTOperator = NextTOperator::getInstance();
    }
protected:
    //NextTOperator* nextTOperator;
    // to insert cache class

};


#endif //SPA_CACHECLAUSEEVALUATOR_H
