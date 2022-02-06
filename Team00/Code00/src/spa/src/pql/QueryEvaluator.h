//
// Created by リム・イーサン on 30/1/22.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H


#include "PKB.h"
#include "pql/query_obj/Query.h"

class QueryEvaluator {
private:
    PKB* pkb;
public:
    QueryEvaluator(PKB* pkb) : pkb(pkb) { }
    std::string evaluate(Query* query);
};


#endif //SPA_QUERYEVALUATOR_H
