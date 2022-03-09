//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_SELECTCLAUSEEVALUATOR_H
#define SPA_SELECTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class SelectClauseEvaluator : public ClauseEvaluator {
public:
    SelectClauseEvaluator (PKB* pkb, Query* query) : ClauseEvaluator(pkb, query) {};
    bool evaluateClause(ResultTable* resultTable) override;
private:
    bool applyAttrRef(std::vector<std::string>*, std::pair<string, AttrName>, std::vector<std::string>*);
    std::vector<std::string> getMapping(std::vector<std::string>&, std::string (*func) (std::string))
    int appendMapping(ResultTable *resultTable, long index, pair<string, AttrName> attrRef, string (*func)(string));
};


#endif //SPA_SELECTCLAUSEEVALUATOR_H
