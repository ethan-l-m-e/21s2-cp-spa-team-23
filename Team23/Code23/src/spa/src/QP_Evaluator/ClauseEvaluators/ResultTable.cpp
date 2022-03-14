//
// Created by Tianyi Wang on 9/2/22.
//

#include "ResultTable.h"

#include <utility>

ResultTable::ResultTable(){
    tableHeader = std::vector<std::string>{};
    tableEntries = String2DVector{};
    isBooleanResult = false;
    booleanResult = true;
}

ResultTable::ResultTable(std::vector<std::string> header, String2DVector values){
    tableHeader = std::move(header);
    tableEntries = std::move(values);
    isBooleanResult = false;
}

void ResultTable::clearTable() {
    tableHeader = std::vector<std::string>{};
    tableEntries = String2DVector{};
}

void ResultTable::enableBooleanResult() {
    isBooleanResult = true;
}

bool ResultTable::isBoolean(){
    return isBooleanResult;
}

bool ResultTable::isEmpty(){
    return tableEntries.empty();
}

bool ResultTable::getBooleanResult() {
    return booleanResult;
}

std::string ResultTable::getBooleanResultString() {
    return booleanResult ? "TRUE" : "FALSE";
}

std::vector<std::string>* ResultTable::getHeader() {
    return &tableHeader;
}

String2DVector* ResultTable::getList() {
    return &tableEntries;
}

size_t ResultTable::getTableSize() {
    if(isEmpty()) return 0;
    return tableEntries[0].size();
}

size_t ResultTable::getTableWidth() {
    if(isEmpty()) return 0;
    return tableEntries.size();
}

void ResultTable::setBooleanResult(bool result) {
    booleanResult = result;
}

void ResultTable::appendColumn(std::string colName, std::vector<std::string>& col) {
    tableHeader.emplace_back(colName);
    tableEntries.emplace_back(col);
}

void ResultTable::rearrangeSynonyms(std::vector<int>& orders) {
    std::vector<std::string> newHeader = {};
    String2DVector newEntries = {};
    for(auto order : orders) {
        if(order < 0 || order >= tableHeader.size()) return;
        newHeader.emplace_back(tableHeader[order]);
        newEntries.emplace_back(tableEntries[order]);
    }
    tableHeader = newHeader;
    tableEntries = newEntries;
}

/**
 * Merge a result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeResultToTable(Result& result) {
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
 * Compute cross product of the table and a string result and assign the updated values to the table.
 * @param synonymValues  reference to the list of ResultItem of the type string
 */
void ResultTable::crossJoinStrings(std::vector<ResultItem>& synonymValues) {
    if(tableEntries.empty()) {
        tableEntries.emplace_back(std::vector<std::string>());
        for(auto resultItem : synonymValues) {
            auto curr = std::get<std::string>(resultItem);
            tableEntries[0].emplace_back(curr);
        }
    } else {
        size_t length = tableEntries[0].size();
        std::unordered_map<std::string, std::vector<std::string>> snapshot = createSnapShot();
        tableEntries.emplace_back(std::vector<std::string>());

        for (auto resultItem = synonymValues.begin(); resultItem != synonymValues.end(); ++resultItem) {
            for (auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
                long index = std::distance(tableEntries.begin(), it);
                std::vector<std::string> values;
                if(it == tableEntries.end() - 1) {
                    values.insert(values.end(), length, std::get<std::string>(*resultItem));
                } else {
                    if(resultItem == synonymValues.begin()) {
                        values = {};
                    } else {
                        values = snapshot.find(tableHeader[index])->second;
                    }
                }
                it->insert(it->end(), values.begin(), values.end());
            }
        }
    }
}

/**
 * Compute cross product of the table and a tuple result and assign the updated values to the table.
 * @param synonymValues  reference to the list of ResultItem of the type tuple
 */
void ResultTable::crossJoinTuples(std::vector<ResultItem>& synonymValues) {
    String2DVector updatedTuples;

    for(auto resultItem : synonymValues) {
        auto curr = std::get<std::tuple<std::string,std::string>>(resultItem);

        for (const auto &value: tableEntries) {
            //deep copy values
            std::vector<std::string> currentValues = value;
            currentValues.emplace_back(std::get<0>(curr));
            currentValues.emplace_back(std::get<1>(curr));
            updatedTuples.emplace_back(currentValues);
        }
    }
    if(tableEntries.empty()) {
        tableEntries.insert(tableEntries.end(), 2, std::vector<std::string>());
        for(auto resultItem : synonymValues) {
            auto curr = std::get<std::tuple<std::string,std::string>>(resultItem);
            tableEntries[0].emplace_back(std::get<0>(curr));
            tableEntries[1].emplace_back(std::get<1>(curr));
        }
    } else {
        size_t length = tableEntries[0].size();
        std::unordered_map<std::string, std::vector<std::string>> snapshot = createSnapShot();
        tableEntries.insert(tableEntries.end(), 2, std::vector<std::string>());
        for (auto resultItem = synonymValues.begin(); resultItem != synonymValues.end(); ++resultItem) {
            for (auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
                long index = std::distance(tableEntries.begin(), it);
                std::vector<std::string> values;
                if(it == tableEntries.end() - 2) {
                    values.insert(values.end(),length,
                                  std::get<0>(std::get<std::tuple<std::string,std::string>>(*resultItem)));
                } else if (it == tableEntries.end() - 1) {
                    values.insert(values.end(), length,
                                  std::get<1>(std::get<std::tuple<std::string,std::string>>(*resultItem)));
                } else {
                    if(resultItem == synonymValues.begin()) {
                        values = {};
                    } else {
                        values = snapshot.find(tableHeader[index])->second;
                    }
                }
                it->insert(it->end(), values.begin(), values.end());
            }
        }
    }
}

/**
 * Inner join method to join the table with a string result, with a common synonym.
 * @param index  the index of the common synonym in the table header
 * @param resultItemList  a list of ResultItem of the type string
 */
void ResultTable::innerJoin(size_t index, std::vector<ResultItem>& resultItemList) {
    for (int i= 0; i< tableEntries[index].size();) {
        if (!std::count(resultItemList.begin(), resultItemList.end(), (ResultItem) (tableEntries[index][i]))) {
            for(auto & tableEntry : tableEntries)
                tableEntry.erase(tableEntry.begin() + i);
        } else {
            ++i;
        }
    }
}

/**
 * Inner join method to join the table with a tuple result, with two common synonyms.
 * @param indices  pair of indices representing the position of the two synonyms in the table header
 * @param resultItemList  a list of ResultItem of the type tuple
 */
void ResultTable::innerJoin(std::pair<size_t, size_t> indices, std::vector<ResultItem>& resultItemList) {
    for (int i= 0; i< tableEntries[indices.first].size();) {
        std::string left = tableEntries[indices.first][i];
        std::string right = tableEntries[indices.second][i];
        std::tuple<std::string, std::string> curr = make_tuple(left, right);
        if (!std::count(resultItemList.begin(), resultItemList.end(), (ResultItem) curr)) {
            for(auto & tableEntry : tableEntries)
                tableEntry.erase(tableEntry.begin() + i);
        } else {
            ++i;
        }
    }
}

/**
 * Inner join method to join the table with a tuple result, with one common synonym.
 * @param index  the index of the common synonym in the table header
 * @param map  an unordered map representation of the tuple result with the values of the common synonym as the key
 */
void ResultTable::innerJoin(size_t index, std::unordered_map<std::string,std::vector<std::string>> map){
    // for each row
    size_t oldSize = tableEntries[0].size();
    tableEntries.emplace_back(std::vector<std::string>());
    for (int i = 0; i < oldSize;) {
        auto it = map.find(tableEntries[index][i]);
        if (it != map.end()) {
            std::vector<std::string> rightSet = it->second;
            size_t numNewRows = rightSet.size();
            for (auto col = tableEntries.begin(); col != tableEntries.end(); ++col) {
                if(col == tableEntries.end() - 1) {
                    for (const auto& right: rightSet )
                        col->emplace_back(right);
                } else {
                    col->insert(col->end(), numNewRows, (*col)[i]);
                    col->erase(col->begin() + i);
                }
            }
        } else {
            for (auto col = tableEntries.begin(); col != tableEntries.end() - 1; ++col) {
                col->erase(col->begin() + i);
            }
        }
        oldSize -= 1;
    }
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

std::unordered_map<std::string, std::vector<std::string>> ResultTable::createSnapShot() {
    std::unordered_map<std::string, std::vector<std::string>> snapshot;
    for (auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
        long index = std::distance(tableEntries.begin(), it);
        std::vector<std::string> temp;
        temp.assign(it->begin(), it->end());
        snapshot.insert(std::pair<std::string,std::vector<std::string>>(tableHeader[index], temp));
    }
    return snapshot;
}




