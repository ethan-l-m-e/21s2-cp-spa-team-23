//
// Created by Tianyi Wang on 9/2/22.
//

#include "SynonymRelations.h"

#include <utility>

SynonymRelations::SynonymRelations(){
    nTupleHeader = std::vector<std::string>{};
    nTupleList = std::vector<std::vector<std::string>>{};
}

SynonymRelations::SynonymRelations(std::vector<std::string> header,std::vector<std::vector<std::string>> values){
    nTupleHeader = std::move(header);
    nTupleList = std::move(values);
};

bool SynonymRelations::isEmpty(){
    return nTupleList.empty();
}

std::vector<std::string>* SynonymRelations::getHeader() {
    return &nTupleHeader;
}

std::vector<std::vector<std::string>>* SynonymRelations::getList() {
    return &nTupleList;
}

void SynonymRelations::assignList(std::vector<std::vector<std::string>> newList) {
    nTupleList = std::move(newList);
}

void SynonymRelations::mergeResultToSynonymsRelations(Result& result) {
    //if result is boolean type, do nothing;
    if (result.resultType == ResultType::BOOLEAN) return;

    // if result is list of string
    if (result.resultType == ResultType::STRING) {
        auto it = std::find(nTupleHeader.begin(), nTupleHeader.end(), std::get<std::string>(result.resultHeader));

        // if synonym is not in the relation, append new synonym
        if (it == nTupleHeader.end()) {
            //append new synonym to header
            nTupleHeader.emplace_back(std::get<std::string>(result.resultHeader));
            //assign new list
            assignList(appendNewSynonym(nTupleList, result.resultItemList));

            // if synonym is in the relation
        } else {

            long index = std::distance(nTupleHeader.begin(), it);
            for (auto value = nTupleList.begin(); value != nTupleList.end();) {
                std::string curr = (*value)[index];
                if (!std::count(result.resultItemList.begin(), result.resultItemList.end(),
                                (ResultItem) (*value)[index])) {
                    nTupleList.erase(value);
                } else {
                    ++value;
                }
            }
        }

        // if result is list of tuples
    } else if (result.resultType == ResultType::TUPLES) {
        auto headerTuple = std::get<std::tuple<std::string, std::string>>(result.resultHeader);
        auto it1 = std::find(nTupleHeader.begin(), nTupleHeader.end(), std::get<0>(headerTuple));
        auto it2 = std::find(nTupleHeader.begin(), nTupleHeader.end(), std::get<1>(headerTuple));

        // if both synonym are not in the relation, append new tuples
        if (it1 == nTupleHeader.end() && it2 == nTupleHeader.end()) {
            //append new synonym tuple to header
            nTupleHeader.emplace_back(std::get<0>(headerTuple));
            nTupleHeader.emplace_back(std::get<1>(headerTuple));
            //assign new list
            assignList(appendNewSynonymTuples(nTupleList, result.resultItemList));

            // if both synonym are in the relation, join the tuples
        } else if (it1 != nTupleHeader.end() && it2 != nTupleHeader.end()) {
            long index1 = std::distance(nTupleHeader.begin(), it1);
            long index2 = std::distance(nTupleHeader.begin(), it2);
            for (auto value = nTupleList.begin(); value != nTupleList.end();) {
                std::string left = (*value)[index1];
                std::string right = (*value)[index2];
                std::tuple<std::string, std::string> curr = make_tuple(left, right);
                if (!std::count(result.resultItemList.begin(), result.resultItemList.end(),
                                (ResultItem) curr)) {
                    nTupleList.erase(value);
                } else {
                    ++value;
                }
            }
            // if only one synonym is in the relation, join the tuples
        } else if (it1 != nTupleHeader.end()) {
            auto map =  convertVectorToMap(result.resultItemList, false);
            long index1 = std::distance(nTupleHeader.begin(), it1);
            std::vector<std::vector<std::string>> updatedTuples;
            for (auto & value : nTupleList) {
                std::string left = value[index1];
                auto it = map.find(left);
                if (it != map.end()) {
                    std::vector<std::string> rightSet = it->second;
                    for (const auto& right: rightSet ) {
                        std::vector<std::string> updatedValue = value;
                        updatedValue.emplace_back(right);
                        updatedTuples.emplace_back(updatedValue);
                    }
                }
            }
            nTupleHeader.emplace_back(std::get<1>(headerTuple));
            assignList(updatedTuples);
        } else{
            auto map =  convertVectorToMap(result.resultItemList, true);
            long index2 = std::distance(nTupleHeader.begin(), it2);
            std::vector<std::vector<std::string>> updatedTuples;
            for (auto & value : nTupleList) {
                std::string right = value[index2];
                auto it = map.find(right);
                if (it != map.end()) {
                    std::vector<std::string> leftSet = it->second;
                    for (const auto& left: leftSet ) {
                        std::vector<std::string> updatedValue = value;
                        updatedValue.emplace_back(left);
                        updatedTuples.emplace_back(updatedValue);
                    }
                }
            }
            nTupleHeader.emplace_back(std::get<0>(headerTuple));
            assignList(updatedTuples);

        }
    }

    if(nTupleList.empty()) {
        nTupleHeader = {};
    }
}


std::unordered_map<std::string, std::vector<std::string>> SynonymRelations::convertVectorToMap (std::vector<ResultItem>& resultItemList, bool reversed) {
    std::unordered_map<std::string, std::vector<std::string>> map;
    for(auto resultItem : resultItemList) {
        auto curr = std::get<std::tuple<std::string,std::string>>(resultItem);
        if (reversed) {
            std::string s1 = std::get<0>(curr);
            std::string s2 = std::get<1>(curr);
            curr = std::tuple<std::string,std::string>{s2, s1};
        }
        auto it = map.find(std::get<0>(curr));
        if(it != map.end()) {
            std::vector<std::string> value = it->second;
            value.emplace_back(std::get<1>(curr));
            it->second = value;
        } else {
            map.insert({std::get<0>(curr), {std::get<1>(curr)}});
        }
    }

    return map;
}

std::vector<std::vector<std::string>> SynonymRelations::appendNewSynonym(std::vector<std::vector<std::string>>& currentTuples, std::vector<ResultItem>& synonymValues) {
    std::vector<std::vector<std::string>> updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<std::string>(resultItem);
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

std::vector<std::vector<std::string>> SynonymRelations::appendNewSynonymTuples(std::vector<std::vector<std::string>>& currentTuples, std::vector<ResultItem>& synonymValues) {
    std::vector<std::vector<std::string>> updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<std::tuple<std::string,std::string>>(resultItem);
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

