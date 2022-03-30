//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_CLAUSEEVALUATOR_H
#define SPA_CLAUSEEVALUATOR_H

#include "QP_Evaluator/Query/Query.h"
#include "PKB/PKB.h"
#include "Result.h"
#include "ResultTable.h"

class ClauseEvaluator {
protected:
    Clause* clause;
    unordered_map<string, DesignEntity>* declarations;
    PKB* pkb;
    Result result;
    bool processResult(ResultTable* resultTable);
    bool applyAttrRef(std::pair<string, AttrName> &attrRef, string (ClauseEvaluator::* *func)(string&),
                      string *name);
    string getVarRead(string&);
    string getVarPrinted(string&);
    string getProcByCall(string&);
    vector<string> getMapping(vector<string>& lst, string (ClauseEvaluator::*func)(string&));
    unordered_map<string, string> generateMap(unordered_set<string>& set, string (ClauseEvaluator::*func)(string&));
    unordered_map<string, string> generateMap(unordered_set<string>& set);
    Result makeResult(bool validity);
    Result makeResult(string header, unordered_set<string> values);
    Result makeResult(pair<string, string> header, unordered_set<pair<string, string>> values);
public:
    ClauseEvaluator(unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb) : declarations(declarations), clause(clause),  pkb(pkb){}
    virtual ~ClauseEvaluator() = default;
    virtual bool evaluateClause(ResultTable* resultTable) = 0;
    unordered_set<string> getAllType(DesignEntity designEntity);

};


#endif //SPA_CLAUSEEVALUATOR_H
