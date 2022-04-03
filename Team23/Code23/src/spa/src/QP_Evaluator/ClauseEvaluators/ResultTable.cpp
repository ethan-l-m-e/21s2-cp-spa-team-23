//
// Created by Tianyi Wang on 9/2/22.
//

#include "ResultTable.h"

#include <utility>

ResultTable::ResultTable(){
    tableHeader = vector<string>{};
    tableEntries = String2DVector{};
    isBooleanResult = false;
    booleanResult = true;
}

void ResultTable::setResultTable(vector<string> header, String2DVector values){
    tableHeader = std::move(header);
    tableEntries = std::move(values);
    isBooleanResult = false;
    booleanResult = true;
}

void ResultTable::clearTable() {
    tableHeader = vector<string>{};
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

string ResultTable::getBooleanResultString() {
    return booleanResult ? "TRUE" : "FALSE";
}

vector<string>* ResultTable::getHeader() {
    return &tableHeader;
}

String2DVector* ResultTable::getList() {
    return &tableEntries;
}

size_t ResultTable::getTableHeight() {
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

void ResultTable::appendColumn(string colName, vector<string>& col) {
    tableHeader.emplace_back(colName);
    tableEntries.emplace_back(col);
}

void ResultTable::rearrangeSynonyms(vector<int>& orders) {
    vector<string> newHeader = {};
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
    } else if (result.resultType == ResultType::SINGLE) {
        mergeStringResult(result);
    } else if (result.resultType == ResultType::PAIR) {
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
    auto stringSet = std::get<unordered_set<string>>(result.resultSet);
    auto header = std::get<string>(result.resultHeader);
    auto it = std::find(tableHeader.begin(), tableHeader.end(), header);
    if (it == tableHeader.end()) {
        // compute cross product if the synonym is not in the header
        appendHeader({std::get<string>(result.resultHeader)});
        crossJoinStrings(stringSet);
    } else {
        // otherwise, do an inner join
        innerJoin(std::distance(tableHeader.begin(), it), stringSet);
    }
}

/**
 * Merge a tuples result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeTuplesResult(Result& result) {
    auto tupleSet = std::get<unordered_set<pair<string, string>>>(result.resultSet);
    auto headerTuple = std::get<pair<string, string>>(result.resultHeader);
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
void ResultTable::appendHeader(const vector<string>& synonymList) {
    for (const auto& synonym : synonymList) {
        tableHeader.emplace_back(synonym);
    }
}

/**
 * Compute cross product of the table and a string result and assign the updated values to the table.
 * @param synonymValues  reference to the ResultSet of the type string
 */
void ResultTable::crossJoinStrings(unordered_set<string>& synonymValues) {
    if(tableEntries.empty()) {
        tableEntries.emplace_back(vector<string>());
        for(const auto& resultItem : synonymValues) {
            tableEntries[0].emplace_back(resultItem);
        }
    } else {
        size_t length = tableEntries[0].size();
        unordered_map<string, vector<string>> snapshot = createSnapShot();
        tableEntries.emplace_back(vector<string>());

        for (auto resultItem = synonymValues.begin(); resultItem != synonymValues.end(); ++resultItem) {
            for (auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
                long index = std::distance(tableEntries.begin(), it);
                vector<string> values;
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
void ResultTable::crossJoinTuples(unordered_set<pair<string, string>>& synonymValues) {
    if(tableEntries.empty()) {
        tableEntries.insert(tableEntries.end(), 2, vector<string>());
        for(const auto& resultItem : synonymValues) {
            auto curr = resultItem;
            tableEntries[0].emplace_back(curr.first);
            tableEntries[1].emplace_back(curr.second);
        }
    } else {
        size_t length = tableEntries[0].size();
        unordered_map<string, vector<string>> snapshot = createSnapShot();
        tableEntries.insert(tableEntries.end(), 2, vector<string>());
        for (auto resultItem = synonymValues.begin(); resultItem != synonymValues.end(); ++resultItem) {
            for (auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
                long index = std::distance(tableEntries.begin(), it);
                vector<string> values;
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

void ResultTable::innerJoin(size_t index, unordered_set<string>& resultItemList) {
   size_t height = getTableHeight();
   size_t width = getTableWidth();
   unordered_set<int> deletedRows;
   for (int r = 0; r < height; r++) {
       if (!std::count(resultItemList.begin(), resultItemList.end(), tableEntries[index][r])) {
           deletedRows.insert(r);
       }
   }
   for (int c = 0; c < width; c++) {
       vector<string> newValues;
       for (int r = 0; r < height; r++) {
           if(deletedRows.find(r) != deletedRows.end()) continue;
           newValues.emplace_back(tableEntries[c][r]);
       }
       tableEntries[c] = newValues;
   }
}

/**
 * Inner join method to join the table with a tuple result, with two common synonyms.
 * @param indices  pair of indices representing the position of the two synonyms in the table header
 * @param resultItemList  a list of ResultItem of the type tuple
 */

void ResultTable::innerJoin(std::pair<size_t, size_t> indices, unordered_set<pair<string, string>>& resultItemList) {
    size_t height = getTableHeight();
    size_t width = getTableWidth();
    unordered_set<int> deletedRows;
    for (int r = 0; r < height; r++) {
        string left = tableEntries[indices.first][r];
        string right = tableEntries[indices.second][r];
        if (!std::count(resultItemList.begin(), resultItemList.end(), make_pair(left, right))) {
            deletedRows.insert(r);
        }
    }

    for (int c = 0; c < width; c++) {
        vector<string> newValues;
        for (int r = 0; r < height; r++) {
            if(deletedRows.find(r) != deletedRows.end()) continue;
            newValues.emplace_back(tableEntries[c][r]);
        }
        tableEntries[c] = newValues;
    }
}

/**
 * Inner join method to join the table with a tuple result, with one common synonym.
 * @param index  the index of the common synonym in the table header
 * @param map  an unordered map representation of the tuple result with the values of the common synonym as the key
 */

void ResultTable::innerJoin(size_t index, unordered_map<string,vector<string>> map){
    size_t height = getTableHeight();
    size_t width = getTableWidth();
    std::unordered_set<int> deletedRows;
    tableEntries.emplace_back(vector<string>());

    for (int r = 0; r < height; r++) {
        auto it = map.find(tableEntries[index][r]);
        if (it == map.end()) {
            deletedRows.insert(r);
        } else {
            auto newCol = tableEntries[width];
            tableEntries[width].insert(tableEntries[width].end(), it->second.begin(), it->second.end());
        }
    }

    for (int c = 0; c < width; c++) {
        std::vector<std::string> newValues;
        for (int r = 0; r < height; r++) {
            if(deletedRows.find(r) != deletedRows.end()) continue;
            auto it = map.find(tableEntries[index][r]);
            newValues.insert(newValues.end(), (it->second).size(), tableEntries[c][r]);
        }
        tableEntries[c] = newValues;
    }
}

/**
 * Convert a result set of pairs to an unordered map with the first value in the pair as the key. (right value if flipped)
 * @param resultItemList  reference to the result set of pairs
 * @param flipped  a boolean to indicate whether to generate the map with the second value as the key
 * @return  an unordered map representation of the original tuples vector
 */
unordered_map<string, vector<string>> ResultTable::convertToMap (unordered_set<pair<string, string>>& resultItemList, bool flipped) {
    unordered_map<string, vector<string>> map;
    for(const auto& resultItem : resultItemList) {
        pair<string,string> curr = resultItem;
        if (flipped) {
            string s1 = resultItem.first;
            string s2 = resultItem.second;
            curr = pair<string,string>{s2, s1};
        }
        auto it = map.find(curr.first);
        if(it != map.end()) {
            vector<string> value = it->second;
            value.emplace_back(curr.second);
            it->second = value;
        } else {
            map.insert({curr.first, {curr.second}});
        }
    }

    return map;
}

unordered_map<string, vector<string>> ResultTable::createSnapShot() {
    unordered_map<string, vector<string>> snapshot;
    for (auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
        long index = std::distance(tableEntries.begin(), it);
        vector<string> temp;
        temp.assign(it->begin(), it->end());
        snapshot.insert(pair<string,vector<string>>(tableHeader[index], temp));
    }
    return snapshot;
}

vector<int> ResultTable::getProjection() {
    if (projection.empty()) {
        vector<int> defaultProjection;
        defaultProjection.reserve(tableHeader.size());
        for( int i = 0; i < tableHeader.size(); i++ ) defaultProjection.emplace_back( i );
        return defaultProjection;
    } else {
        return projection;
    }
}




