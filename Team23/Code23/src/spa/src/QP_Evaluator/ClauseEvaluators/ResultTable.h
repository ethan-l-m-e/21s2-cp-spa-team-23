//
// Created by Tianyi Wang on 9/2/22.
//

#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include "Result.h"

#include <utility>
#include <unordered_map>
#include <string>
#include <vector>

using String2DVector = std::vector<std::vector<std::string>>;


class ResultTable {
public:
    ResultTable();
    ResultTable(std::vector<std::string>, String2DVector);
    void clearTable();
    bool isBoolean();
    bool isEmpty();
    std::string getBooleanResult();
    std::vector<std::string> *getHeader();
    String2DVector *getList();
    size_t getTableSize();
    void setBooleanResult(bool);
    void appendColumn(std::string, std::vector<std::string>&);
    void mergeResultToTable(Result &result);
    void rearrangeSynonyms(std::vector<int>&);

private:
    void mergeStringResult(Result &result);
    void mergeTuplesResult(Result &result);
    void appendHeader(const std::vector<std::string>&);
    void crossJoinStrings(std::vector<ResultItem>&);
    void crossJoinTuples(std::vector<ResultItem>&);
    void innerJoin(size_t, std::vector<ResultItem>&);
    void innerJoin(std::pair<size_t, size_t>, std::vector<ResultItem>&);
    void innerJoin(size_t, std::unordered_map<std::string,std::vector<std::string>>);
    static std::unordered_map<std::string, std::vector<std::string>> convertVectorToMap(std::vector<ResultItem>&, bool);
    std::unordered_map<std::string, std::vector<std::string>> createSnapShot();

    std::vector<std::string> tableHeader;
    String2DVector tableEntries;
    bool isBooleanResult;
    bool booleanResult;
};

#endif //SPA_RESULTTABLE_H
