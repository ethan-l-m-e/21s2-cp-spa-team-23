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


class SynonymRelations {
public:
    SynonymRelations();
    SynonymRelations(std::vector<std::string>, std::vector<std::vector<std::string>>);
    bool isEmpty();
    std::vector<std::string> *getHeader();
    std::vector<std::vector<std::string>> *getList();
    void mergeResultToSynonymsRelations(Result& result);


private:
    void assignList(std::vector<std::vector<std::string>> newList);
    std::unordered_map<std::string, std::vector<std::string>> convertVectorToMap(std::vector<ResultItem>&, bool);
    std::vector<std::vector<std::string>> appendNewSynonym(std::vector<std::vector<std::string>>&, std::vector<ResultItem>&);
    std::vector<std::vector<std::string>> appendNewSynonymTuples(std::vector<std::vector<std::string>>&, std::vector<ResultItem>&);

    std::vector<std::string> nTupleHeader;
    std::vector<std::vector<std::string>> nTupleList;
};

#endif //SPA_SYNONYMRELATIONS_H
