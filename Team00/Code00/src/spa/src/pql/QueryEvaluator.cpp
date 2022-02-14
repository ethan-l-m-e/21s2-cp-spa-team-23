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
        //string test = std::get<std::string>(selectResult.resultItemList[0]);
        //cout << test;
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
    std::vector<std::string>* header  = sr->getHeader();
    std::vector<std::vector<std::string>>* values = sr->getList();
    auto headerType = result.resultHeader.index();
    if (headerType == 0) {
        auto it = std::find(header->begin(), header->end(), std::get<string>(result.resultHeader));
        if(it != header->end()) {
            long index = std::distance( header->begin(), it );
            for (auto value = values->begin(); value != values->end(); ++value)
            {
                if (!std::count(result.resultItemList.begin(), result.resultItemList.end(), (ResultItem)(*value)[index])) {
                    values->erase(value);
                }
            }
        } else {
            //append new synonym to header

            header->emplace_back(std::get<string>(result.resultHeader));

            //assign new list
            auto* updatedValues = new std::vector<std::vector<std::string>>{};
            if(values->empty()){
                for(auto resultItem : result.resultItemList) {
                    std::string curr = std::get<string>(resultItem);
                    updatedValues->emplace_back(std::vector<std::string>{curr});
                }
            } else {
                for (auto resultItem: result.resultItemList) {
                    std::string curr = std::get<string>(resultItem);
                    //append to existing values
                    for (const auto &value: *values) {
                        //deep copy values
                        std::vector<std::string> currentValues = value;
                        currentValues.emplace_back(curr);
                        updatedValues->emplace_back(currentValues);
                    }
                }
            }
            sr->assignList(updatedValues);
        }
    } else {
        // more logic
    }

}

std::list<std::string> QueryEvaluator::generateResultString(SynonymRelations* sr, string selectedSynonym) {

    std::list<std::string> stringList;
    std::vector<std::string>* header  = sr->getHeader();
    for(size_t j = 0; j < header->size(); ++j) {
        std::string str = (*header)[j];
        if (str == selectedSynonym) {
            std::vector<std::vector<std::string>>* vec = sr->getList();
            std::string s;
            for(auto & i : *vec)
            {
                s = i[j];
                stringList.emplace_back(s);
            }
            return stringList;
        }
    }
    return stringList;
}