//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H


#include "PKB.h"
#include "pql/query_obj/Query.h"
#include "pql/ClauseEvaluators/Result.h"
#include "pql/ClauseEvaluators/ClauseEvaluator.h"

#include <sstream>
#include <iostream>
#include <list>

class QueryEvaluator {
private:
    PKB* pkb;
public:
    explicit QueryEvaluator(PKB* pkb) : pkb(pkb) { }

    std::list<std::string> evaluate(Query*);

    ClauseEvaluator* generateEvaluator(SuchThatClause&, Query*);

    static std::list<std::string> generateResultString(Result&);

    static void mergeResultToSynonymsRelations(SynonymRelations&, Result&);

    static vector<std::vector<std::string>> appendNewSynonym(vector<vector<std::string>>&, vector<ResultItem>&);

    static vector<std::vector<std::string>> appendNewSynonymTuples(vector<vector<std::string>>&, vector<ResultItem>&);

    static unordered_map<std::string, std::vector<string>> convertVectorToMap (std::vector<ResultItem>&, bool);
};


#endif //SPA_QUERYEVALUATOR_H
