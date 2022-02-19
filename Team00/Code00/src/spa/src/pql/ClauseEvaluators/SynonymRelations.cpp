//
// Created by Tianyi Wang on 9/2/22.
//

#include "SynonymRelations.h"

#include <utility>

SynonymRelations::SynonymRelations(){
    tableHeader = std::vector<std::string>{};
    tableEntries = String2DVector{};
}

SynonymRelations::SynonymRelations(std::vector<std::string> header,String2DVector values){
    tableHeader = std::move(header);
    tableEntries = std::move(values);
};

bool SynonymRelations::isEmpty(){
    return tableEntries.empty();
}

std::vector<std::string>* SynonymRelations::getHeader() {
    return &tableHeader;
}

String2DVector* SynonymRelations::getList() {
    return &tableEntries;
}

void SynonymRelations::updateEntries(String2DVector newList) {
    tableEntries = std::move(newList);
}

void SynonymRelations::mergeResultToSynonymsRelations(Result& result) {
    //if result is boolean type, do nothing;
    if (result.resultType == ResultType::BOOLEAN) {
        return;
    } else if (result.resultType == ResultType::STRING) {
        mergeStringResult(result);
    } else if (result.resultType == ResultType::TUPLES) {
        mergeTuplesResult(result);
    }

    if(tableEntries.empty()) {
        tableHeader = {};
    }
}

void SynonymRelations::mergeStringResult(Result& result) {
    auto it = std::find(tableHeader.begin(), tableHeader.end(), std::get<std::string>(result.resultHeader));
    if (it == tableHeader.end()) {
        // compute cross product if the synonym is not in the header
        appendHeader({std::get<std::string>(result.resultHeader)});
        appendNewSynonym(tableEntries, result.resultItemList);
    } else {
        // otherwise, do an inner join
        innerJoin(std::distance(tableHeader.begin(), it), result.resultItemList);
    }
}

void SynonymRelations::mergeTuplesResult(Result& result) {
    auto headerTuple = std::get<std::tuple<std::string, std::string>>(result.resultHeader);
    auto it1 = std::find(tableHeader.begin(), tableHeader.end(), std::get<0>(headerTuple));
    auto it2 = std::find(tableHeader.begin(), tableHeader.end(), std::get<1>(headerTuple));

    if (it1 == tableHeader.end() && it2 == tableHeader.end()) {
        // compute cross product if both the synonyms are not in the header
        appendHeader({std::get<0>(headerTuple), std::get<1>(headerTuple)});
        appendNewSynonymTuples(tableEntries, result.resultItemList);
    } else if (it1 != tableHeader.end() && it2 != tableHeader.end()) {
        innerJoin(std::make_pair(std::distance(tableHeader.begin(), it1), std::distance(tableHeader.begin(), it2)),
                  result.resultItemList);
    } else if (it1 != tableHeader.end()) {
        innerJoin(std::distance(tableHeader.begin(), it1),
                  convertVectorToMap(result.resultItemList, false));
        appendHeader({std::get<1>(headerTuple)});
    } else{
        innerJoin(std::distance(tableHeader.begin(), it2),
                  convertVectorToMap(result.resultItemList, true));
        appendHeader({std::get<0>(headerTuple)});
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


void SynonymRelations::appendNewSynonym(String2DVector& currentTuples, std::vector<ResultItem>& synonymValues) {
    String2DVector updatedTuples;

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
    updateEntries(updatedTuples);
};

void SynonymRelations::appendNewSynonymTuples(String2DVector& currentTuples, std::vector<ResultItem>& synonymValues) {
    String2DVector updatedTuples;

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
    updateEntries(updatedTuples);
};


void SynonymRelations::appendHeader(const std::vector<std::string>& synonymList) {
    for (const auto& synonym : synonymList) {
        tableHeader.emplace_back(synonym);
    }
}


void SynonymRelations::innerJoin(size_t index, std::vector<ResultItem>& resultItemList) {
    for (auto value = tableEntries.begin(); value != tableEntries.end();) {
        std::string curr = (*value)[index];
        if (!std::count(resultItemList.begin(), resultItemList.end(),
                        (ResultItem) (*value)[index])) {
            tableEntries.erase(value);
        } else {
            ++value;
        }
    }
}

void SynonymRelations::innerJoin(std::pair<size_t, size_t> index, std::vector<ResultItem>& resultItemList) {
    for (auto value = tableEntries.begin(); value != tableEntries.end();) {
        std::string left = (*value)[index.first];
        std::string right = (*value)[index.second];
        std::tuple<std::string, std::string> curr = make_tuple(left, right);
        if (!std::count(resultItemList.begin(), resultItemList.end(),
                        (ResultItem) curr)) {
            tableEntries.erase(value);
        } else {
            ++value;
        }
    }
}

void SynonymRelations::innerJoin(size_t index, std::unordered_map<std::string,std::vector<std::string>> map){
    String2DVector updatedTuples;
    for (auto & value : tableEntries) {
        std::string left = value[index];
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
    updateEntries(updatedTuples);
}