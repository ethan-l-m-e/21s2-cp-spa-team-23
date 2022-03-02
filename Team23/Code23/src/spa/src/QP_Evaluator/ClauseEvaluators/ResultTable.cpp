//
// Created by Tianyi Wang on 9/2/22.
//

#include "ResultTable.h"

#include <utility>

ResultTable::ResultTable(){
    tableHeader = std::vector<std::string>{};
    tableEntries = String2DVector{};
}

ResultTable::ResultTable(std::vector<std::string> header, String2DVector values){
    tableHeader = std::move(header);
    tableEntries = std::move(values);
}

bool ResultTable::isEmpty(){
    return tableEntries.empty();
}

std::vector<std::string>* ResultTable::getHeader() {
    return &tableHeader;
}

String2DVector* ResultTable::getList() {
    return &tableEntries;
}

/**
 * Merge a result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeResultToSynonymsRelations(Result& result) {
    //if result is boolean type, do nothing;
    if (result.resultType == ResultType::BOOLEAN) {
        return;
    } else if (result.resultType == ResultType::STRING) {
        mergeStringResult(result);
    } else if (result.resultType == ResultType::TUPLES) {
        mergeTuplesResult(result);
    }

    // clear the table headers if there is no entry in the table left.
    if(tableEntries.empty()) {
        tableHeader = {};
    }
}

/**
 * Merge a string result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeStringResult(Result& result) {
    auto it = std::find(tableHeader.begin(), tableHeader.end(), std::get<std::string>(result.resultHeader));
    if (it == tableHeader.end()) {
        // compute cross product if the synonym is not in the header
        appendHeader({std::get<std::string>(result.resultHeader)});
        crossJoinStrings(result.resultItemList);
    } else {
        // otherwise, do an inner join
        innerJoin(std::distance(tableHeader.begin(), it), result.resultItemList);
    }
}

/**
 * Merge a tuples result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeTuplesResult(Result& result) {
    auto headerTuple = std::get<std::tuple<std::string, std::string>>(result.resultHeader);
    auto it1 = std::find(tableHeader.begin(), tableHeader.end(), std::get<0>(headerTuple));
    auto it2 = std::find(tableHeader.begin(), tableHeader.end(), std::get<1>(headerTuple));

    if (it1 == tableHeader.end() && it2 == tableHeader.end()) {
        // compute cross product if both the synonyms are not in the header
        appendHeader({std::get<0>(headerTuple), std::get<1>(headerTuple)});
        crossJoinTuples(result.resultItemList);
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

/**
 * Append a list of synonyms to the table header.
 * @param synonymList  reference to the list of synonyms to be appended
 */
void ResultTable::appendHeader(const std::vector<std::string>& synonymList) {
    for (const auto& synonym : synonymList) {
        tableHeader.emplace_back(synonym);
    }
}

/**
 * Replace the current table entries with a new set of entries.
 * @param newList  a new vector of table entries to replace the current table entries
 */
void ResultTable::updateEntries(String2DVector newList) {
    tableEntries = std::move(newList);
}

/**
 * Compute cross product of the table and a string result and assign the updated values to the table.
 * @param synonymValues  reference to the list of ResultItem of the type string
 */
void ResultTable::crossJoinStrings(std::vector<ResultItem>& synonymValues) {
    String2DVector updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<std::string>(resultItem);
        if(tableEntries.empty()) {
            updatedTuples.emplace_back(std::vector<std::string>{curr});
        } else {
            for (const auto &value: tableEntries) {
                //deep copy values
                std::vector<std::string> currentValues = value;
                currentValues.emplace_back(curr);
                updatedTuples.emplace_back(currentValues);
            }
        }
    }
    updateEntries(updatedTuples);
}

/**
 * Compute cross product of the table and a tuple result and assign the updated values to the table.
 * @param synonymValues  reference to the list of ResultItem of the type tuple
 */
void ResultTable::crossJoinTuples(std::vector<ResultItem>& synonymValues) {
    String2DVector updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<std::tuple<std::string,std::string>>(resultItem);
        if(tableEntries.empty()) {
            auto vector = std::vector<std::string> {std::get<0>(curr), std::get<1>(curr)};
            updatedTuples.emplace_back(vector);
        } else {
            for (const auto &value: tableEntries) {
                //deep copy values
                std::vector<std::string> currentValues = value;
                currentValues.emplace_back(std::get<0>(curr));
                currentValues.emplace_back(std::get<1>(curr));
                updatedTuples.emplace_back(currentValues);
            }
        }
    }
    updateEntries(updatedTuples);
}

/**
 * Inner join method to join the table with a string result, with a common synonym.
 * @param index  the index of the common synonym in the table header
 * @param resultItemList  a list of ResultItem of the type string
 */
void ResultTable::innerJoin(size_t index, std::vector<ResultItem>& resultItemList) {
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

/**
 * Inner join method to join the table with a tuple result, with two common synonyms.
 * @param indices  pair of indices representing the position of the two synonyms in the table header
 * @param resultItemList  a list of ResultItem of the type tuple
 */
void ResultTable::innerJoin(std::pair<size_t, size_t> indices, std::vector<ResultItem>& resultItemList) {
    for (auto value = tableEntries.begin(); value != tableEntries.end();) {
        std::string left = (*value)[indices.first];
        std::string right = (*value)[indices.second];
        std::tuple<std::string, std::string> curr = make_tuple(left, right);
        if (!std::count(resultItemList.begin(), resultItemList.end(),
                        (ResultItem) curr)) {
            tableEntries.erase(value);
        } else {
            ++value;
        }
    }
}

/**
 * Inner join method to join the table with a tuple result, with one common synonym.
 * @param index  the index of the common synonym in the table header
 * @param map  an unordered map representation of the tuple result with the values of the common synonym as the key
 */
void ResultTable::innerJoin(size_t index, std::unordered_map<std::string,std::vector<std::string>> map){
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

/**
 * Convert a vector of ResultItem to an unordered map with the left value in the tuple as the key. (right value if flipped)
 * @param resultItemList  reference to the list of ResultItem of the type tuple
 * @param flipped  a boolean to indicate whether to generate the map with the right value as the key
 * @return  an unordered map representation of the original tuples vector
 */
std::unordered_map<std::string, std::vector<std::string>> ResultTable::convertVectorToMap (std::vector<ResultItem>& resultItemList, bool flipped) {
    std::unordered_map<std::string, std::vector<std::string>> map;
    for(auto resultItem : resultItemList) {
        auto curr = std::get<std::tuple<std::string,std::string>>(resultItem);
        if (flipped) {
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