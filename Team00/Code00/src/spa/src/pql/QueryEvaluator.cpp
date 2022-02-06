//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"

std::string QueryEvaluator::evaluate(Query* query) {
    return query->generateResult(pkb);
}
