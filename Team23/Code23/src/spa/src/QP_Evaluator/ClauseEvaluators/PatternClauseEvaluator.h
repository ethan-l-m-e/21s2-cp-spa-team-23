//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_PATTERNCLAUSEEVALUATOR_H
#define SPA_PATTERNCLAUSEEVALUATOR_H

#include "ClauseEvaluator.h"
#include "QP_Evaluator/Query/Argument.h"
#include "TNode/Node.h"

class PatternClauseEvaluator : public ClauseEvaluator {
public:
    PatternClauseEvaluator (unordered_map<string, DesignEntity>* declarations, Clause* clause, PKB* pkb): ClauseEvaluator(declarations, clause, pkb) {
        patternSynonymType = static_cast<PatternClause*>(clause)->synonymType;
    }
    bool evaluateClause(ResultTable* resultTable) override;
protected:
    SynonymType patternSynonymType;

    Argument patternSynonym = clause->argList[0];
    Argument arg1 = clause->argList[1];
    Argument arg2 = clause->argList[2];
    //the last argument will be processed if pattern-syn is if

    // get argument 3 if is if-node
    bool evaluateAssign(ResultTable *resultTable);
    bool evaluateWhile(ResultTable *resultTable);
    bool evaluateIf(ResultTable *resultTable);

    void constructResults(ResultItems results, bool hasTuples);

    bool evaluateWithFunc_Pointers(ResultTable *resultTable,
                                   void (*validateAndParse)(Argument, Argument, Argument, Expression, Expression),
                                   ResultItems (*collectResults)(Argument, Argument, Expression, Expression));
};


#endif //SPA_PATTERNCLAUSEEVALUATOR_H