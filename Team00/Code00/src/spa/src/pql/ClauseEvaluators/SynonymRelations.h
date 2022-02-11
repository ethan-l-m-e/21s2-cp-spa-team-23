//
// Created by Tianyi Wang on 9/2/22.
//

#ifndef SPA_SYNONYMRELATIONS_H
#define SPA_SYNONYMRELATIONS_H

#include <string>
#include <vector>

class SynonymRelations {
public:
    SynonymRelations();
    bool isEmpty();
    std::vector<std::string>* getHeader();
    std::vector<std::vector<std::string>>* getList();

private:
    std::vector<std::string> nTupleHeader;
    std::vector<std::vector<std::string>> nTupleList;
};

#endif //SPA_SYNONYMRELATIONS_H
