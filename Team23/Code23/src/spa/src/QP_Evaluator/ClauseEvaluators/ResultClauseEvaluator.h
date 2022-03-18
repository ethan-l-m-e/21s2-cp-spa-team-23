//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_RESULTCLAUSEEVALUATOR_H
#define SPA_RESULTCLAUSEEVALUATOR_H


#include "ClauseEvaluator.h"

class ResultClauseEvaluator : public ClauseEvaluator {
public:
    ResultClauseEvaluator(PKB *pkb, Query *query) : ClauseEvaluator(pkb, query) {};

    bool evaluateClause(ResultTable *resultTable) override;

private:
    void projectSelectedSynonyms(vector<int> *, ResultTable *);

    bool applyAttrRef(std::pair<string, AttrName> &attrRef, std::string (ResultClauseEvaluator::* *func)(std::string&),
                      std::string *name);

    std::vector<std::string> getMapping(std::vector<std::string> &, std::string (ResultClauseEvaluator::*func)(std::string&));

    string getVarRead(string&);

    string getVarPrinted(string&);

    string getProcByCall(string&);

    void appendNewSynonym(string, ResultTable*);

    void updateTableForAttrReference(std::pair<string, AttrName>&, long*, ResultTable*);

    static void unpackSynonym(Argument&, std::pair<string, AttrName>*, string*);

};

#endif //SPA_RESULTCLAUSEEVALUATOR_H
