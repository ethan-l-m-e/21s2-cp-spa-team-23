//
// Created by Tin Hong Wen on 22/3/22.
//

#ifndef SPA_CACHECLAUSEEVALUATOR_H
#define SPA_CACHECLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"
#include "Cache/Cache.h"
class CacheClauseEvaluator: public SuchThatClauseEvaluator {
public:
    CacheClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): SuchThatClauseEvaluator(declarations, clause, pkb) {}
    bool setOptimisation(bool in);
protected:
    Cache* cache = Cache::getInstance();
    //false: runs without caching
    // true: runs with caching
    bool optimisation_activated = true;

};


#endif //SPA_CACHECLAUSEEVALUATOR_H
