//
// Created by リム・イーサン on 30/1/22.
//

#include "QueryEvaluator.h"


std::list<std::string> QueryEvaluator::evaluate(Query* query) {
    // Initialise an empty result
    auto* synonymRelations = new SynonymRelations();

    // Create ClauseEvaluators and evaluate each of the pattern clause
    if(query->hasPatternClause()) {
        for(const PatternClause& clause : query->getPatternClauses()) {
            auto patternClauseEvaluator = new PatternClauseEvaluator(clause.synonymType, clause.argList, pkb, query);
            Result patternResult = patternClauseEvaluator->evaluateClause();
            delete patternClauseEvaluator;
            if (!patternResult.resultBoolean) return {};
            mergeResultToSynonymsRelations(*synonymRelations, patternResult);
        }
    }

    // Create ClauseEvaluators and evaluate each of the suchThat clause
    if(query->hasSuchThatClause()) {
        for(const SuchThatClause& clause : query->getSuchThatClauses()) {
            auto suchThatClauseEvaluator = generateEvaluator(clause, query);
            Result suchThatResult = suchThatClauseEvaluator->evaluateClause();
            delete suchThatClauseEvaluator;
            if (!suchThatResult.resultBoolean) return {};
            mergeResultToSynonymsRelations(*synonymRelations, suchThatResult);
        }
    }

    auto* selectClauseEvaluator = new SelectClauseEvaluator(synonymRelations, pkb, query);
    Result selectResult = selectClauseEvaluator->evaluateClause();
    delete selectClauseEvaluator;
    delete synonymRelations;
    return generateResultString(selectResult);
}

ClauseEvaluator* QueryEvaluator::generateEvaluator(SuchThatClause clause, Query* query) {
    switch (clause.relRef) {
        case RelRef::FOLLOWS:
            return new FollowsClauseEvaluator(clause.argList, pkb, query);
        case RelRef::PARENT:
            return new ParentClauseEvaluator(clause.argList, pkb, query);
        case RelRef::FOLLOWS_T:
            return new FollowsTClauseEvaluator(clause.argList, pkb, query);
        case RelRef::PARENT_T:
            return new ParentTClauseEvaluator(clause.argList, pkb, query);
        case RelRef::USES_S:
            return new UsesSClauseEvaluator(clause.argList, pkb, query);
        case RelRef::USES_P:
            // return new UsesPClauseEvaluator(clause.argList, pkb, query);
        case RelRef::MODIFIES_S:
            return new ModifiesSClauseEvaluator(clause.argList, pkb, query);
        case RelRef::MODIFIES_P:
            // return ModifiesPClauseEvaluator(clause.argList, pkb, query);
        default:
            return new FollowsClauseEvaluator(clause.argList, pkb, query); // TODO: Throw error.
    }
}

std::list<std::string> QueryEvaluator::generateResultString(Result& result) {
    std::list<std::string> stringList;

    if (result.resultType == ResultType::STRING && !result.resultItemList.empty()) {
        for (auto &resultItem: result.resultItemList) {
            auto s = std::get<std::string>(resultItem);
            stringList.emplace_back(s);
        }
    }
    return stringList;
}

void QueryEvaluator::mergeResultToSynonymsRelations(SynonymRelations& sr, Result& result) {
    //if result is boolean type, do nothing;
    if (result.resultType == ResultType::BOOLEAN) return;

    std::vector<std::string>* header  = sr.getHeader();
    std::vector<std::vector<std::string>>* values = sr.getList();

    // if result is list of string
    if (result.resultType == ResultType::STRING) {
        auto it = std::find(header->begin(), header->end(), std::get<string>(result.resultHeader));

        // if synonym is not in the relation, append new synonym
        if (it == header->end()) {
            //append new synonym to header
            header->emplace_back(std::get<string>(result.resultHeader));
            //assign new list
            sr.assignList(appendNewSynonym(*values, result.resultItemList));

        // if synonym is in the relation
        } else {

            long index = std::distance(header->begin(), it);
            for (auto value = values->begin(); value != values->end();) {
                string curr = (*value)[index];
                if (!std::count(result.resultItemList.begin(), result.resultItemList.end(),
                                (ResultItem) (*value)[index])) {
                    values->erase(value);
                } else {
                    ++value;
                }
            }
        }

    // if result is list of tuples
    } else if (result.resultType == ResultType::TUPLES) {
        auto headerTuple = std::get<tuple<string, string>>(result.resultHeader);
        auto it1 = std::find(header->begin(), header->end(), std::get<0>(headerTuple));
        auto it2 = std::find(header->begin(), header->end(), std::get<1>(headerTuple));

        // if both synonym are not in the relation, append new tuples
        if (it1 == header->end() && it2 == header->end()) {
            //append new synonym tuple to header
            header->emplace_back(std::get<0>(headerTuple));
            header->emplace_back(std::get<1>(headerTuple));
            //assign new list
            sr.assignList(appendNewSynonymTuples(*values, result.resultItemList));

        // if both synonym are in the relation, join the tuples
        } else if (it1 != header->end() && it2 != header->end()) {
            long index1 = std::distance(header->begin(), it1);
            long index2 = std::distance(header->begin(), it2);
            for (auto value = values->begin(); value != values->end();) {
                std::string left = (*value)[index1];
                std::string right = (*value)[index2];
                std::tuple<std::string, std::string> curr = make_tuple(left, right);
                if (!std::count(result.resultItemList.begin(), result.resultItemList.end(),
                                (ResultItem) curr)) {
                    values->erase(value);
                } else {
                    ++value;
                }
            }
        // if only one synonym is in the relation, join the tuples
        } else if (it1 != header->end()) {
            auto map =  convertVectorToMap(result.resultItemList, false);
            long index1 = std::distance(header->begin(), it1);
            std::vector<std::vector<std::string>> updatedTuples;
            for (auto & value : *values) {
                std::string left = value[index1];
                auto it = map.find(left);
                if (it != map.end()) {
                    vector<string> rightSet = it->second;
                    for (const auto& right: rightSet ) {
                        std::vector<std::string> updatedValue = value;
                        updatedValue.emplace_back(right);
                        updatedTuples.emplace_back(updatedValue);
                    }
                }
            }
            header->emplace_back(std::get<1>(headerTuple));
            sr.assignList(updatedTuples);
        } else{
            auto map =  convertVectorToMap(result.resultItemList, true);
            long index2 = std::distance(header->begin(), it2);
            std::vector<std::vector<std::string>> updatedTuples;
            for (auto & value : *values) {
                std::string right = value[index2];
                auto it = map.find(right);
                if (it != map.end()) {
                    vector<string> leftSet = it->second;
                    for (const auto& left: leftSet ) {
                        std::vector<std::string> updatedValue = value;
                        updatedValue.emplace_back(left);
                        updatedTuples.emplace_back(updatedValue);
                    }
                }
            }
            header->emplace_back(std::get<0>(headerTuple));
            sr.assignList(updatedTuples);

        }
    }

}

std::vector<std::vector<std::string>> QueryEvaluator::appendNewSynonym(vector<vector<std::string>>& currentTuples, vector<ResultItem>& synonymValues) {
    std::vector<std::vector<std::string>> updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<string>(resultItem);
        if(currentTuples.empty()) {
            updatedTuples.emplace_back(std::vector<std::string>{curr});
        } else {
            for (const auto &value: currentTuples) {
                //deep copy values
                std::vector<std::string> currentValues = value;
                currentValues.emplace_back(curr);
                updatedTuples.emplace_back(currentValues);
            }
        }
    }

    return updatedTuples;
};

std::vector<std::vector<std::string>> QueryEvaluator::appendNewSynonymTuples(vector<vector<string>>& currentTuples, std::vector<ResultItem>& synonymValues) {
    std::vector<std::vector<std::string>> updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<tuple<string,string>>(resultItem);
        if(currentTuples.empty()) {
            auto vector = std::vector<std::string> {std::get<0>(curr), std::get<1>(curr)};
            updatedTuples.emplace_back(vector);
        } else {
            for (const auto &value: currentTuples) {
                //deep copy values
                std::vector<std::string> currentValues = value;
                currentValues.emplace_back(std::get<0>(curr));
                currentValues.emplace_back(std::get<1>(curr));
                updatedTuples.emplace_back(currentValues);
            }
        }
    }

    return updatedTuples;
};

unordered_map<std::string, std::vector<string>> QueryEvaluator::convertVectorToMap (std::vector<ResultItem>& resultItemList, bool reversed) {
    unordered_map<std::string, std::vector<string>> map;
    for(auto resultItem : resultItemList) {
        auto curr = std::get<tuple<string,string>>(resultItem);
        if (reversed) {
            std::string s1 = std::get<0>(curr);
            std::string s2 = std::get<1>(curr);
            curr = tuple<string,string>{s2, s1};
        }
        auto it = map.find(std::get<0>(curr));
        if(it != map.end()) {
            std::vector<string> value = it->second;
            value.emplace_back(std::get<1>(curr));
            it->second = value;
        } else {
            map.insert({std::get<0>(curr), {std::get<1>(curr)}});
        }
    }

    return map;
}

