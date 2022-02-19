//
// Created by Tianyi Wang on 9/2/22.
//

#ifndef SPA_SYNONYMRELATIONS_H
#define SPA_SYNONYMRELATIONS_H

#include "Result.h"

#include <utility>
#include <unordered_map>
#include <string>
#include <vector>

using String2DVector = std::vector<std::vector<std::string>>;


class SynonymRelations {
public:
    SynonymRelations();
    SynonymRelations(std::vector<std::string>, String2DVector);
    bool isEmpty();
    std::vector<std::string> *getHeader();
    String2DVector *getList();
    void mergeResultToSynonymsRelations(Result& result);
private:
    void updateEntries(String2DVector newList);
    void mergeStringResult(Result &result);
    void mergeTuplesResult(Result &result);
    void appendNewSynonym(String2DVector&, std::vector<ResultItem>&);
    void appendNewSynonymTuples(String2DVector&, std::vector<ResultItem>&);
    void appendHeader(const std::vector<std::string>&);
    void innerJoin(size_t, std::vector<ResultItem>&);
    void innerJoin(std::pair<size_t, size_t>, std::vector<ResultItem>&);
    void innerJoin(size_t index, std::unordered_map<std::string,std::vector<std::string>>);
    std::unordered_map<std::string, std::vector<std::string>> convertVectorToMap(std::vector<ResultItem>&, bool);

    std::vector<std::string> tableHeader;
    String2DVector tableEntries;
};

#endif //SPA_SYNONYMRELATIONS_H
