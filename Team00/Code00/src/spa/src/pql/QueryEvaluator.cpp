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
*/

    // Create ClauseEvaluators and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(const SuchThatClause& clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator->evaluateClause();
            //if (!suchThatResult.resultBoolean) return generateResultString(*suchThatResult, query->getSelectedSynonym());
            mergeResultToSynonymsRelations(synonymRelations, suchThatResult);
        }
    }



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
            sr->assignList(appendNewSynonym(values, result.resultItemList));
        }
    } else {
        // more logic
        auto headerTuple = std::get<tuple<string, string>>(result.resultHeader);
        auto it1 = std::find(header->begin(), header->end(), std::get<0>(headerTuple));
        auto it2 = std::find(header->begin(), header->end(), std::get<1>(headerTuple));
        if (it1 == header->end() && it2 == header->end()) {
            //append new synonym tuple to header
            header->emplace_back(std::get<0>(headerTuple));
            header->emplace_back(std::get<1>(headerTuple));
            //assign new list
            sr->assignList(appendNewSynonymTuples(values, result.resultItemList));
        } else if (it1 != header->end() && it1 != header->end()) {
            cout << "join 2 unimplemented";
        } else if (it1 != header->end()) {
            cout << "join 3 unimplemented";
        } else{
            cout << "join 4 unimplemented";
        }
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

std::vector<std::vector<std::string>>* QueryEvaluator::appendNewSynonym(vector<vector<std::string>>* currentTuples, vector<ResultItem> synonymValues) {
    auto* updatedTuples = new std::vector<std::vector<std::string>>{};

    for(auto resultItem : synonymValues) {
        auto curr = std::get<string>(resultItem);
        if(currentTuples->empty()) {
            updatedTuples->emplace_back(std::vector<std::string>{curr});
        } else {
            for (const auto &value: *currentTuples) {
                //deep copy values
                std::vector<std::string> currentValues = value;
                currentValues.emplace_back(curr);
                updatedTuples->emplace_back(currentValues);
            }
        }
    }

    return updatedTuples;
};

std::vector<std::vector<std::string>>* QueryEvaluator::appendNewSynonymTuples(vector<vector<string>>* currentTuples, std::vector<ResultItem> synonymValues) {
    auto* updatedTuples = new std::vector<std::vector<std::string>>{};

    for(auto resultItem : synonymValues) {
        auto curr = std::get<tuple<string,string>>(resultItem);
        if(currentTuples->empty()) {
            auto vector = std::vector<std::string> {std::get<0>(curr), std::get<1>(curr)};
            updatedTuples->emplace_back(vector);
        } else {
            for (const auto &value: *currentTuples) {
                //deep copy values
                std::vector<std::string> currentValues = value;
                currentValues.emplace_back(std::get<0>(curr));
                currentValues.emplace_back(std::get<1>(curr));
                updatedTuples->emplace_back(currentValues);
            }
        }
    }

    return updatedTuples;
};

