//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_RESULTCLAUSEEVALUATOR_H
#define SPA_RESULTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class ResultClauseEvaluator : public ClauseEvaluator {
public:
    ResultClauseEvaluator (PKB* pkb, Query* query) : ClauseEvaluator(pkb, query) {};
    bool evaluateClause(ResultTable* resultTable) override;
private:
    bool applyAttrRef(std::vector<std::string>*, std::pair<string, AttrName>, std::vector<std::string>*);
    std::vector<std::string> getMapping(std::vector<std::string>&, std::string (ResultClauseEvaluator::*func) (std::string));
    string getVarRead(string stmtNumber);
    string getVarPrinted(string stmtNumber);
    string getProcByCall(string stmtNumber);
};


#endif //SPA_RESULTCLAUSEEVALUATOR_H
