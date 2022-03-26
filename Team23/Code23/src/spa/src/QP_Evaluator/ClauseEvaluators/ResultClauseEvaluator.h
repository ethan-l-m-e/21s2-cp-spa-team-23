//
// Created by Tianyi Wang on 7/2/22.
//

#ifndef SPA_RESULTCLAUSEEVALUATOR_H
#define SPA_RESULTCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"

class ResultClauseEvaluator : public ClauseEvaluator {
public:
    ResultClauseEvaluator(unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb) : ClauseEvaluator(declarations, clause, pkb) {};

    bool evaluateClause(ResultTable *resultTable) override;

private:

    void projectSelectedSynonyms(vector<int> *, ResultTable *);

    void appendNewSynonym(string, ResultTable*);

    void updateTableForAttrReference(std::pair<string, AttrName>&, long*, ResultTable*);

    static void unpackSynonym(Argument&, std::pair<string, AttrName>*, string*);

};

#endif //SPA_RESULTCLAUSEEVALUATOR_H
