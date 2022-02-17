//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H


#include "PKB.h"
#include "pql/query_obj/Query.h"
#include "pql/ClauseEvaluators/Result.h"
#include "pql/ClauseEvaluators/ClauseEvaluator.h"
#include "pql/ClauseEvaluators/FollowsClauseEvaluator.h"
#include "pql/ClauseEvaluators/ParentClauseEvaluator.h"
#include "pql/ClauseEvaluators/PatternClauseEvaluator.h"
#include "pql/ClauseEvaluators/SelectClauseEvaluator.h"
#include "pql/ClauseEvaluators/FollowsTClauseEvaluator.h"
#include "pql/ClauseEvaluators/ParentTClauseEvaluator.h"
#include "pql/ClauseEvaluators/ModifiesSClauseEvaluator.h"
#include "pql/ClauseEvaluators/UsesSClauseEvaluator.h"


#include <sstream>
#include <iostream>
#include <list>

class QueryEvaluator {
private:
    PKB* pkb;
public:
    explicit QueryEvaluator(PKB* pkb) : pkb(pkb) { }

    std::list<std::string> evaluate(Query*);

    ClauseEvaluator* generateEvaluator(SuchThatClause, Query*);

    static std::list<std::string> generateResultString(SynonymRelations*, std::string);

    static void mergeResultToSynonymsRelations(SynonymRelations&, Result&);

    static vector<std::vector<std::string>> appendNewSynonym(vector<vector<std::string>>&, vector<ResultItem>&);

    static vector<std::vector<std::string>> appendNewSynonymTuples(vector<vector<std::string>>&, vector<ResultItem>&);

    static unordered_map<std::string, std::vector<string>> convertVectorToMap (std::vector<ResultItem>&, bool);
};


#endif //SPA_QUERYEVALUATOR_H
