//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_SUCHTHATCLAUSEEVALUATOR_H
#define SPA_SUCHTHATCLAUSEEVALUATOR_H


#include <vector>
#include "ClauseEvaluator.h"

enum class RelRef{
    FOLLOWS,
    FOLLOWS_T,
    PARENT,
    PARENT_T,
    USES_S,
    USES_P,
    MODIFIES_S,
    MODIFIES_P
};

class SuchThatClauseEvaluator : public ClauseEvaluator {
private:
    RelRef relRef;
public:
    SuchThatClauseEvaluator(RelRef relRef, std::vector<Argument> args) : relRef(relRef), ClauseEvaluator(args) {}
    Result evaluateClause(PKB* pkb,
                          unordered_map<string, DesignEntity> declarations) override;
    Result evaluateFollows();
    Result evaluateFollowsT();
    Result evaluateParent();
    Result evaluateParentT();
    Result evaluateModifiesS();
    Result evaluateModifiesP();
    Result evaluateUsesS();
    Result evaluateUsesP();
    optional<DesignEntity> findEntityType(std::string synonym);

};


#endif //SPA_SUCHTHATCLAUSEEVALUATOR_H
