//
// Created by Karan Dev Sapra on 12/3/22.
//

#pragma once

#ifndef SPA_STATEMENTTABLE_H
#define SPA_STATEMENTTABLE_H

#include <stdio.h>
#include <unordered_set>
#include <unordered_map>

#include "TNode/TNode.h"

using namespace std;

template<class N>
class StatementTable {


private:

    unordered_set<string> statementNumbersSet;
    unordered_set<N> statementNodesSet;

    unordered_map<string, unordered_set<string>> procedureNameToSetStatementNumbersMap;
    unordered_map<string, string> statementNumberToProcedureNameMap;

public:


    void addStatement(N node);

    unordered_set<string> getStatementNumbersInSameProcedure(string statementNumber);

    bool areInSameProcedure(string statementA, string statementB);




    bool isStatementNumber(string statementNumber);
    unordered_set<string> getAllStatementNumbers();

    unordered_set<N> getAllStatementNodes();


    virtual void clear();
};

#endif //SPA_TABLECLAUSEEVALUATOR_H


template<class N>
void StatementTable<N>::addStatement(N node) {

    string statementNumber = std::to_string(node->getStmtNumber());

    statementNumbersSet.insert(statementNumber);
    statementNodesSet.insert(node);


    Node *n = node->getProc();
    ProcedureNode *procedureNode = dynamic_cast<ProcedureNode *>(n);

    string procedureName = procedureNode->getProcName();

    if (procedureNameToSetStatementNumbersMap.find(procedureName) == procedureNameToSetStatementNumbersMap.end()) {
        procedureNameToSetStatementNumbersMap.emplace(procedureName, unordered_set<string>{statementNumber});
    } else {
        procedureNameToSetStatementNumbersMap[procedureName].insert(statementNumber);
    }

    statementNumberToProcedureNameMap[statementNumber] = procedureName;

}

template<class N>
unordered_set<string> StatementTable<N>::getStatementNumbersInSameProcedure(string statementNumber) {
    string procedureName = statementNumberToProcedureNameMap[statementNumber];
    return procedureNameToSetStatementNumbersMap[procedureName];
}

template<class N>
bool StatementTable<N>::areInSameProcedure(string statementA, string statementB) {
    return statementNumberToProcedureNameMap.find(statementA) != statementNumberToProcedureNameMap.end() &&
           statementNumberToProcedureNameMap.find(statementB) != statementNumberToProcedureNameMap.end() &&
           statementNumberToProcedureNameMap[statementA] == statementNumberToProcedureNameMap[statementB];
}



template<class N>
bool StatementTable<N>::isStatementNumber(string statementNumber) {
    return statementNumbersSet.find(statementNumber) != statementNumbersSet.end();
}

template<class N>
unordered_set<string> StatementTable<N>::getAllStatementNumbers() {
    return statementNumbersSet;
}

template<class N>
unordered_set<N> StatementTable<N>::getAllStatementNodes() {
    return statementNodesSet;
}


template<class N>
void StatementTable<N>::clear() {
    statementNumbersSet.clear();
    statementNodesSet.clear();

    procedureNameToSetStatementNumbersMap.clear();
    statementNumberToProcedureNameMap.clear();
}