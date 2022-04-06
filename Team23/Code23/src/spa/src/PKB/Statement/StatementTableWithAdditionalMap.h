//
// Created by Karan Dev Sapra on 6/4/22.
//

#pragma once

#ifndef SPA_STATEMENTTABLEWITHADDITIONALMAP_H
#define SPA_STATEMENTTABLEWITHADDITIONALMAP_H

#include "StatementTable.h"

template<class N>
class StatementTableWithAdditionalMap : public StatementTable<N> {

private:
    unordered_map<string, string> additionalMap;
protected:
    virtual string getKeyFromNode(N node) = 0;
    virtual string getValueFromNode(N node) = 0;
public:
    void addStatement(N node);
    string getValueFromKey(string key);
    void clear();

};


#endif //SPA_STATEMENTTABLEWITHADDITIONALMAP_H

template<class N>
void StatementTableWithAdditionalMap<N>::addStatement(N node) {
    StatementTable<N>::addStatement(node);
    additionalMap.emplace(getKeyFromNode(node), getValueFromNode(node));
}

template<class N>
string StatementTableWithAdditionalMap<N>::getValueFromKey(string key) {
    return additionalMap[key];
}

template<class N>
void StatementTableWithAdditionalMap<N>::clear() {
    StatementTable<N>::clear();
    additionalMap.clear();
}