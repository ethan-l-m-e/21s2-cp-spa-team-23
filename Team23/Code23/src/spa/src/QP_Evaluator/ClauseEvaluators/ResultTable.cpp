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

vector<string>* ResultTable::getColumn(string& synonym) {
    auto it = find(tableHeader.begin(), tableHeader.end(), synonym);
    if (it != tableHeader.end())
    {
        size_t index = it - tableHeader.begin();
        return &tableEntries[index];
    } else {
        return {};
    }
}

vector<string>* ResultTable::getHeader() {
    return &tableHeader;
}

String2DVector* ResultTable::getList() {
    return &tableEntries;
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

void ResultTable::setProjection(vector<int> proj) {
    projection = std::move(proj);
}

void ResultTable::appendColumn(string header, vector<string>& value) {
    tableHeader.emplace_back(header);
    tableEntries.emplace_back(value);
}

/**
 * Merge a list of columns to the table.
 * @param columns  a vector of new columns to be added to the table
 * @param headers  the corresponding headers for each columns
 */
void ResultTable::mergeColumnsToTable(vector<vector<string>> columns, vector<string> headers) {
    crossJoin(std::move(columns), std::move(headers));
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
        mergeSingleResult(result);
    } else if (result.resultType == ResultType::PAIR) {
        mergePairResult(result);
    }

    // clear the table headers if there is no entry in the table left.
    if(tableEntries.empty()) {
        tableHeader = {};
        setBooleanResult(false);
    }
}

/**
 * Merge a single result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergeSingleResult(Result& result) {
    auto stringSet = std::get<unordered_set<string>>(result.resultSet);
    auto header = std::get<string>(result.resultHeader);
    auto it = std::find(tableHeader.begin(), tableHeader.end(), header);
    if (it == tableHeader.end()) {
        // compute cross product if the synonym is not in the header
        vector<string> stringVector (stringSet.begin(), stringSet.end());
        crossJoin({stringVector},
                  {std::get<string>(result.resultHeader)});
    } else {
        // otherwise, do an inner join
        innerJoin(std::distance(tableHeader.begin(), it), stringSet);
    }
}

/**
 * Merge a pair result to the table.
 * @param result  reference to the result object to be merged
 */
void ResultTable::mergePairResult(Result& result) {
    auto tupleSet = std::get<unordered_set<pair<string, string>>>(result.resultSet);
    auto headerTuple = std::get<pair<string, string>>(result.resultHeader);
    auto it1 = std::find(tableHeader.begin(), tableHeader.end(), headerTuple.first);
    auto it2 = std::find(tableHeader.begin(), tableHeader.end(), headerTuple.second);

    if (it1 == tableHeader.end() && it2 == tableHeader.end()) {
        // compute cross product if both the synonyms are not in the header
        crossJoin(getResultColumns(tupleSet),
                  {headerTuple.first, headerTuple.second});
    } else if (it1 != tableHeader.end() && it2 != tableHeader.end()) {
        innerJoin(std::make_pair(std::distance(tableHeader.begin(), it1), std::distance(tableHeader.begin(), it2)),
                  tupleSet);
    } else if (it1 != tableHeader.end()) {
        innerJoin(std::distance(tableHeader.begin(), it1),
                  convertToMap(tupleSet, false), headerTuple.second);
    } else{
        innerJoin(std::distance(tableHeader.begin(), it2),
                  convertToMap(tupleSet, true), headerTuple.first);
    }
}

/**
 * Join a list of new columns to the result table. The list of new columns are treated as set tuples, no cross join is
 * performed between them.
 * @param columns  a list of new columns, none of the columns should exist in the table before joining
 * @param headers  the headers for the list of new columns
 */
void ResultTable::crossJoin(vector<vector<string>> columns, vector<string> headers) {

    if(columns.empty()) return;

    long numRows = (long) (getTableHeight() == 0 ? 1 : getTableHeight());
    long numVals = (long) columns[0].size();

    for (auto & column : tableEntries) {
        std::vector<std::string> temp (column.begin(), column.begin() + numRows);
        for(int i = 0; i < numVals - 1; i++) {
            column.insert(column.end(), temp.begin(), temp.end());
        }
    }

    for (int i = 0; i < columns.size(); i++) {
        vector<string> updatedColumn;
        for ( const auto& value : columns[i]) {
            updatedColumn.insert(updatedColumn.end(), numRows, value);
        }
        appendColumn(headers[i], updatedColumn);
    }
}

/**
 * Inner join method to join the table with a single result set, with a common synonym.
 * @param index  the index of the common synonym in the table header
 * @param resultSet  a set of single results
 */
void ResultTable::innerJoin(size_t index, unordered_set<string>& resultSet) {
   size_t height = getTableHeight();
   size_t width = getTableWidth();
   unordered_set<int> deletedRows;
   for (int r = 0; r < height; r++) {
       if (!resultSet.count(tableEntries[index][r])) {
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
 * Inner join method to join the table with a pair result set, with two common synonyms.
 * @param indices  pair of indices representing the position of the two synonyms in the table header
 * @param resultSet  a set of pair results
 */
void ResultTable::innerJoin(std::pair<size_t, size_t> indices, unordered_set<pair<string, string>>& resultSet) {
    size_t height = getTableHeight();
    size_t width = getTableWidth();
    unordered_set<int> deletedRows;
    for (int r = 0; r < height; r++) {
        string left = tableEntries[indices.first][r];
        string right = tableEntries[indices.second][r];
        if (!resultSet.count(make_pair(left, right))) {
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
 * Inner join method to join the table with a pair result set, with one common synonym.
 * @param index  the index of the common synonym in the table header
 * @param map  an unordered map representation of the tuple result with the values of the common synonym as the key
 * @param newHeader  the synonym to be appended to the header
 */
void ResultTable::innerJoin(size_t index, unordered_map<string,vector<string>> map, string newHeader){
    size_t height = getTableHeight();
    size_t width = getTableWidth();
    std::unordered_set<int> deletedRows;
    vector<string> referenceCol = tableEntries[index];
    vector<string> newCol;

    for (int r = 0; r < height; r++) {
        auto it = map.find(referenceCol[r]);
        if (it == map.end()) {
            deletedRows.insert(r);
        } else {
            newCol.insert(newCol.end(), it->second.begin(), it->second.end());
        }
    }

    for (int c = 0; c < width; c++) {
        std::vector<std::string> newValues;
        for (int r = 0; r < height; r++) {
            if(deletedRows.find(r) != deletedRows.end()) continue;
            auto it = map.find(referenceCol[r]);
            newValues.insert(newValues.end(), (it->second).size(), tableEntries[c][r]);
        }
        tableEntries[c] = newValues;
    }
    appendColumn(std::move(newHeader), newCol);
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

/**
 * Generate two column vectors from a pair result set
 * @param resultSet  a pair result set
 * @return  a vector of 2 vectors representing the first and second item in the result pair
 */
vector<vector<string>> ResultTable::getResultColumns (unordered_set<pair<string, string>>& resultSet) {
    vector<string> row1;
    vector<string> row2;
    for(const auto& pair : resultSet) {
        row1.emplace_back(pair.first);
        row2.emplace_back(pair.second);
    }
    return {row1, row2};
}



