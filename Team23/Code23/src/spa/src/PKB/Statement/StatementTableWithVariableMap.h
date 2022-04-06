//
// Created by Karan Dev Sapra on 6/4/22.
//

#ifndef SPA_STATEMENTTABLEWITHVARIABLEMAP_H
#define SPA_STATEMENTTABLEWITHVARIABLEMAP_H

#include "StatementTableWithAdditionalMap.h"

template<class N>
class StatementTableWithVariableMap : public StatementTableWithAdditionalMap<N> {
private:

    string getKeyFromNode(N node);
    string getValueFromNode(N node);

public:
    string getVariableName(string statementNumber);

};

#endif //SPA_STATEMENTTABLEWITHVARIABLEMAP_H

template<class N>
string StatementTableWithVariableMap<N>::getKeyFromNode(N node) {
    return std::to_string(node->getStmtNumber());
}

template<class N>
string StatementTableWithVariableMap<N>::getValueFromNode(N node) {
    return node->getVarName();
};

template<class N>
string StatementTableWithVariableMap<N>::getVariableName(string statementNumber) {
    return StatementTableWithAdditionalMap<N>::getValueFromKey(statementNumber);
}