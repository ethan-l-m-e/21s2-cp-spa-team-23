//
// Created by Tianyi Wang on 9/2/22.
//

#include "SynonymRelations.h"

SynonymRelations::SynonymRelations(){
    nTupleHeader = std::vector<std::string>{};
    nTupleList = std::vector<std::vector<std::string>>{};
}

bool SynonymRelations::isEmpty(){
    return nTupleList.empty();
}

std::vector<std::string>* SynonymRelations::getHeader() {
    return &nTupleHeader;
}

std::vector<std::vector<std::string>>* SynonymRelations::getList() {
    return &nTupleList;
}

void SynonymRelations::assignList(std::vector<std::vector<std::string>>* newList) {
    nTupleList = *newList;
}