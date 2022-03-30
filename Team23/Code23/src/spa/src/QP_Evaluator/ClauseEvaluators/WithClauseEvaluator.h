//
// Created by Tianyi Wang on 26/3/22.
//

#ifndef SPA_WITHCLAUSEEVALUATOR_H
#define SPA_WITHCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"

class WithClauseEvaluator : public ClauseEvaluator {
public:
    WithClauseEvaluator(unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): ClauseEvaluator(declarations, clause, pkb) {};
    bool evaluateClause(ResultTable* resultTable) override;
protected:
    unordered_set<pair<string, string>> compareAttributes(unordered_map<string, string> leftMap, unordered_map<string, string> rightMap);
    unordered_set<string> compareAttributes(unordered_map<string, string> map, string ident);
    unordered_map<string, string> getAttributeMapping(pair<string, AttrName> argumentValue);

    Argument argLeft = clause->argList[0];
    Argument argRight = clause->argList[1];

};


#endif //SPA_WITHCLAUSEEVALUATOR_H
