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
    void setResultTable(vector<string>, String2DVector);
    void clearTable();
    void enableBooleanResult();
    bool isBoolean();
    bool isEmpty();
    bool getBooleanResult();
    string getBooleanResultString();
    vector<string> *getHeader();
    String2DVector *getList();
    size_t getTableHeight();
    size_t getTableWidth();
    void setBooleanResult(bool);
    void appendColumn(string, vector<string>&);
    void mergeResultToTable(Result &result);
    void rearrangeSynonyms(vector<int>&);
    vector<int> getProjection();
private:
    void updateEntries(String2DVector newList);
    void mergeStringResult(Result &result);
    void mergeTuplesResult(Result &result);
    void appendHeader(const vector<string>&);
    void crossJoin(vector<vector<string>> columns, vector<string> headers);
    void crossJoinStrings(unordered_set<string>&);
    void crossJoinTuples(unordered_set<pair<string, string>>&);
    void innerJoin(size_t, unordered_set<string>&);
    void innerJoin(pair<size_t, size_t>, unordered_set<pair<string, string>>&);
    void innerJoin(size_t, unordered_map<string,vector<string>>);
    static unordered_map<string, vector<string>> convertToMap(unordered_set<pair<string, string>>&, bool);
    unordered_map<string, vector<string>> createSnapShot();
    vector<vector<string>> getResultColumns (unordered_set<pair<string, string>>& resultSet);

    vector<string> tableHeader;
    String2DVector tableEntries;
    bool isBooleanResult;
    bool booleanResult;
    vector<int> projection;
};

#endif //SPA_RESULTTABLE_H
