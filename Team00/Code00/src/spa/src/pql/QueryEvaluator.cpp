//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"


std::list<std::string> QueryEvaluator::evaluate(Query* query) {
    // Initialise an empty result
    auto* synonymRelations = new SynonymRelations();
/*
    // Create ClauseEvaluators and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(PatternClause clause : query->getPatternClauses()) {
            PatternClauseEvaluator patternClauseEvaluator = PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResult = patternClauseEvaluator.evaluateClause();
            if (!patternResult.resultBoolean) return convertResultToString(result, query->getSelectedSynonym());
            result = mergeResults(result, patternResult);
        }
    }

    // Create ClauseEvaluators and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        cout << "has such that clause!!!";
        for(const SuchThatClause& clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator->evaluateClause();
            //if (!suchThatResult.resultBoolean) return generateResultString(*suchThatResult, query->getSelectedSynonym());
            mergeResultToSynonymsRelations(synonymRelations, suchThatResult);
        }
    }

    */

    if (synonymRelations->isEmpty()) {
        auto* selectClauseEvaluator = new SelectClauseEvaluator(synonymRelations, pkb, query);
        Result selectResult = selectClauseEvaluator->evaluateClause();
        mergeResultToSynonymsRelations(synonymRelations, selectResult);
    }

    return generateResultString(synonymRelations, query->getSelectedSynonym());
}

ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause clause, Query* query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
            break;
        /*
        case RelRef::FOLLOWS_T:
            // return FollowsTClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::PARENT:
            // return ParentClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::PARENT_T:
            // return ParentTTClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::USES_S:
            // return UsesSClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::USES_P:
            // return UsesPClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::MODIFIES_S:
            // return ModifiesSClauseEvaluator(clause.argList, pkb, query);
            break;
        case RelRef::MODIFIES_P:
            // return ModifiesPClauseEvaluator(clause.argList, pkb, query);
            break;
        */
        default:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
    }
}

void QueryEvaluator::mergeResultToSynonymsRelations(SynonymRelations* sr, Result result) {
    //TODO: method for merging two results
}

std::list<std::string> QueryEvaluator::generateResultString(SynonymRelations* sr, string selectedSynonym) {

    /*
    std::list<std::string> stringList;
    std::vector<std::string>* header  = sr.getHeader();
    for(size_t j = 0; j < header->size(); ++j) {
        std::string str = (*header)[j];
        if (str == selectedSynonym) {
            std::vector<std::vector<std::string>>* vec = sr.getList();
            std::string s;
            for(auto & i : *vec)
            {
                s = i[j];
                stringList.emplace_back(s);
            }
            return stringList;
        }
    }
     */

    std::list<std::string> stringList;
    stringList.emplace_back("1");
    return stringList;
}

