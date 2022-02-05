//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_SUCHTHATCLAUSEEVALUATOR_H
#define SPA_SUCHTHATCLAUSEEVALUATOR_H


#include <vector>
#include "ClauseEvaluator.h"

class SuchThatClauseEvaluator : public ClauseEvaluator {
private:
    RelRef relRef;
public:
    SuchThatClauseEvaluator(RelRef relRef, std::vector<Argument> args) : relRef(relRef), ClauseEvaluator(args,) {}
    Result evaluateClause(PKB* pkb,
                          unordered_map<string, DesignEntity> declarations) override;
    optional<DesignEntity> findEntityType(std::string synonym);

};


#endif //SPA_SUCHTHATCLAUSEEVALUATOR_H
