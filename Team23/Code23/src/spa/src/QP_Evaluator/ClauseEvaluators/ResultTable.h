//
// Created by Tianyi Wang on 9/2/22.
//

#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include "Result.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using String2DVector = vector<vector<string>>;

class ResultTable {
public:
    ResultTable();
    void clearTable();

    void appendColumn(string header, vector<string>& value);
    void enableBooleanResult();
    void mergeColumnsToTable(vector<vector<string>> columns, vector<string> headers);
    void mergeResultToTable(Result &result);

    // GETTERS
    bool isBoolean();
    bool isEmpty();
    bool getBooleanResult();
    string getBooleanResultString();
    vector<string> *getColumn(string& synonym);
    vector<string> *getHeader();
    String2DVector *getList();
    size_t getTableHeight();
    size_t getTableWidth();
    vector<int> getProjection();

    // SETTERS
    void setBooleanResult(bool);
    void setProjection(vector<int> projection);
    void setResultTable(vector<string>, String2DVector);

private:
    vector<string> tableHeader;
    String2DVector tableEntries;
    bool isBooleanResult;
    bool booleanResult;
    vector<int> projection;

    void mergeSingleResult(Result &result);
    void mergePairResult(Result &result);
    void crossJoin(vector<vector<string>> columns, vector<string> headers);
    void innerJoin(size_t, unordered_set<string>&);
    void innerJoin(pair<size_t, size_t>, unordered_set<pair<string, string>>&);
    void innerJoin(size_t, unordered_map<string,vector<string>>, string);
    static unordered_map<string, vector<string>> convertToMap(unordered_set<pair<string, string>>&, bool);
    vector<vector<string>> getResultColumns (unordered_set<pair<string, string>>& resultSet);
};

#endif //SPA_RESULTTABLE_H
