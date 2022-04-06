//
// Created by Karan Dev Sapra on 6/4/22.
//

#ifndef SPA_STATEMENTTABLEWITHPROCEDUREMAP_H
#define SPA_STATEMENTTABLEWITHPROCEDUREMAP_H


#include "StatementTableWithAdditionalMap.h"

template<class N>
class StatementTableWithProcedureMap : public StatementTableWithAdditionalMap<N> {
private:
    string getKeyFromNode(N node);
    string getValueFromNode(N node);
public:
    string getProcedureName(string statementNumber);
};

#endif //SPA_STATEMENTTABLEWITHPROCEDUREMAP_H


template<class N>
string StatementTableWithProcedureMap<N>::getKeyFromNode(N node) {
    return std::to_string(node->getStmtNumber());
}

template<class N>
string StatementTableWithProcedureMap<N>::getValueFromNode(N node) {
    return node->getProcName();
};

template<class N>
string StatementTableWithProcedureMap<N>::getProcedureName(string statementNumber) {
    return StatementTableWithAdditionalMap<N>::getValueFromKey(statementNumber);
}