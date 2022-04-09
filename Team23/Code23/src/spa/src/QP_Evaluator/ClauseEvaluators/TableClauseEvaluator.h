//
// Created by Tianyi Wang on 26/3/22.
//

#ifndef SPA_TABLECLAUSEEVALUATOR_H
#define SPA_TABLECLAUSEEVALUATOR_H

#include "SuchThatClauseEvaluator.h"
#include "QP_Parser/Exception.h"

template<typename T>
class TableClauseEvaluator : public SuchThatClauseEvaluator {
public:
    TableClauseEvaluator(unordered_map<string, DesignEntity> *declarations, Clause *clause, PKB *pkb, T *relationship)
            : SuchThatClauseEvaluator(declarations, clause, pkb), relationship{relationship} {}

    RelRef getRelRef() override { return dynamic_cast<SuchThatClause *>(clause)->relRef; };
protected:
    T *relationship;

    bool isRelation(string left, string right) override;

    unordered_set<string> getLeftSynonymValue(string right) override;

    unordered_set<string> getRightSynonymValue(string left) override;

    pair<DesignEntity, DesignEntity> getWildcardType() override;
};


#endif //SPA_TABLECLAUSEEVALUATOR_H

template<typename T>
bool TableClauseEvaluator<T>::isRelation(string left, string right) {
    return relationship->isRelationship(left, right);
}

template<typename T>
unordered_set<string> TableClauseEvaluator<T>::getLeftSynonymValue(string right) {
    return relationship->getLHS(right);
}

template<typename T>
unordered_set<string> TableClauseEvaluator<T>::getRightSynonymValue(string left) {
    return relationship->getRHS(left);
}

template<typename T>
pair<DesignEntity, DesignEntity> TableClauseEvaluator<T>::getWildcardType () {
    switch(dynamic_cast<SuchThatClause*>(clause)->relRef) {
        case RelRef::FOLLOWS:
        case RelRef::PARENT:
        case RelRef::FOLLOWS_T:
        case RelRef::PARENT_T:
        case RelRef::NEXT:
            return make_pair(DesignEntity::STMT, DesignEntity::STMT);
        case RelRef::USES_S:
        case RelRef::MODIFIES_S:
            return make_pair(DesignEntity::STMT, DesignEntity::VARIABLE);
        case RelRef::USES_P:
        case RelRef::MODIFIES_P:
            return make_pair(DesignEntity::PROCEDURE, DesignEntity::VARIABLE);
        case RelRef::CALLS:
        case RelRef::CALLS_T:
            return make_pair(DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
        default:
            throw qp::QPEvaluatorException("No valid clause evaluator is found for relationship type");
    }
}
