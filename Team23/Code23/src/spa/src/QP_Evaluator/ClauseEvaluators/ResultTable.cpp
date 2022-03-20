//
// Created by Tianyi Wang on 9/2/22.
//

#include "ResultTable.h"

#include <utility>
#include <unordered_set>

ResultTable::ResultTable(){
    tableHeader = std::vector<std::string>{};
    tableEntries = String2DVector{};
    isBooleanResult = false;
    booleanResult = true;
}

void ResultTable::setResultTable(std::vector<std::string> header, String2DVector values){
    tableHeader = std::move(header);
    tableEntries = std::move(values);
    isBooleanResult = false;
    booleanResult = true;
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
    auto stringSet = std::get<std::unordered_set<std::string>>(result.resultSet);
    auto header = std::get<std::string>(result.resultHeader);
    auto it = std::find(tableHeader.begin(), tableHeader.end(), header);
    if (it == tableHeader.end()) {
        // compute cross product if the synonym is not in the header
        appendHeader({std::get<std::string>(result.resultHeader)});
        crossJoinStrings(stringSet);
    } else {
        // otherwise, do an inner join
        innerJoin(std::distance(tableHeader.begin(), it), result.resultSet);
    }
}

/**
 * Merge a tuples result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeTuplesResult(Result& result) {
    auto tupleSet = std::get<std::unordered_set<std::pair<std::string, std::string>>>(result.resultSet);
    auto headerTuple = std::get<std::pair<std::string, std::string>>(result.resultHeader);
    auto it1 = std::find(tableHeader.begin(), tableHeader.end(), headerTuple.first);
    auto it2 = std::find(tableHeader.begin(), tableHeader.end(), headerTuple.second);

    if (it1 == tableHeader.end() && it2 == tableHeader.end()) {
        // compute cross product if both the synonyms are not in the header
        appendHeader({headerTuple.first, headerTuple.second});
        crossJoinTuples(tupleSet);
    } else if (it1 != tableHeader.end() && it2 != tableHeader.end()) {
        innerJoin(std::make_pair(std::distance(tableHeader.begin(), it1), std::distance(tableHeader.begin(), it2)),
                  tupleSet);
    } else if (it1 != tableHeader.end()) {
        innerJoin(std::distance(tableHeader.begin(), it1),
                  convertToMap(tupleSet, false));
        appendHeader({headerTuple.second});
    } else{
        innerJoin(std::distance(tableHeader.begin(), it2),
                  convertToMap(tupleSet, true));
        appendHeader({headerTuple.first});
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
 * @param synonymValues  reference to the ResultSet of the type string
 */
void ResultTable::crossJoinStrings(std::unordered_set<std::string>& synonymValues) {
    if(tableEntries.empty()) {
        tableEntries.emplace_back(std::vector<std::string>());
        for(const auto& resultItem : synonymValues) {
            auto curr = resultItem;
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
                    values.insert(values.end(), length, *resultItem);
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
void ResultTable::crossJoinTuples(std::unordered_set<std::pair<std::string, std::string>>& synonymValues) {
    if(tableEntries.empty()) {
        tableEntries.insert(tableEntries.end(), 2, std::vector<std::string>());
        for(const auto& resultItem : synonymValues) {
            auto curr = resultItem;
            tableEntries[0].emplace_back(curr.first);
            tableEntries[1].emplace_back(curr.second);
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
                    values.insert(values.end(),length,resultItem->first);
                } else if (it == tableEntries.end() - 1) {
                    values.insert(values.end(), length,resultItem->second);
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
void ResultTable::innerJoin(size_t index, std::unordered_set<std::string>& resultItemList) {
    for (int i= 0; i< tableEntries[index].size();) {
        if (!resultItemList.count(tableEntries[index][i])) {
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
void ResultTable::innerJoin(std::pair<size_t, size_t> indices, std::unordered_set<std::pair<std::string, std::string>>& resultItemList) {
    for (int i= 0; i< tableEntries[indices.first].size();) {
        std::string left = tableEntries[indices.first][i];
        std::string right = tableEntries[indices.second][i];
        std::pair<std::string, std::string> curr = std::make_pair(left, right);
        if (!resultItemList.count(curr)) {
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
 * Convert a result set of pairs to an unordered map with the first value in the pair as the key. (right value if flipped)
 * @param resultItemList  reference to the result set of pairs
 * @param flipped  a boolean to indicate whether to generate the map with the second value as the key
 * @return  an unordered map representation of the original tuples vector
 */
std::unordered_map<std::string, std::vector<std::string>> ResultTable::convertToMap (std::unordered_set<std::pair<std::string, std::string>>& resultItemList, bool flipped) {
    std::unordered_map<std::string, std::vector<std::string>> map;
    for(const auto& resultItem : resultItemList) {
        std::pair<std::string,std::string> curr = resultItem;
        if (flipped) {
            std::string s1 = resultItem.first;
            std::string s2 = resultItem.second;
            curr = std::pair<std::string,std::string>{s2, s1};
        }
        auto it = map.find(curr.first);
        if(it != map.end()) {
            std::vector<std::string> value = it->second;
            value.emplace_back(curr.second);
            it->second = value;
        } else {
            map.insert({curr.first, {curr.second}});
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




