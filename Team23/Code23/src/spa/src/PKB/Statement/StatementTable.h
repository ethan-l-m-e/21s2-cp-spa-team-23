//
// Created by Karan Dev Sapra on 12/3/22.
//

#pragma once

#include<stdio.h>
#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBHelper.h"

#include "TNode/TNode.h"

using namespace std;

//class N;

template<class N>
class StatementTable {


private:

    unordered_set<string> statementNumbersSet;
    unordered_set<N> statementNodesSet;

    unordered_map<string, unordered_set<string>> procedureNameToSetStatementNumbersMap;
    unordered_map<string, string> statementNumberToProcedureNameMap;

public:


    void addStatement(N node) {

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

    unordered_set<string> getStatementNumbersInSameProcedure(string statementNumber) {
        string procedureName = statementNumberToProcedureNameMap[statementNumber];
        return procedureNameToSetStatementNumbersMap[procedureName];
    }

    bool areInSameProcedure(string statementA, string statementB) {
        return statementNumberToProcedureNameMap.find(statementA) != statementNumberToProcedureNameMap.end() &&
        statementNumberToProcedureNameMap.find(statementB) != statementNumberToProcedureNameMap.end() &&
        statementNumberToProcedureNameMap[statementA] == statementNumberToProcedureNameMap[statementB];
    }




    bool isStatementNumber(string statementNumber) {
        return statementNumbersSet.find(statementNumber) != statementNumbersSet.end();
    }

    unordered_set<string> getAllStatementNumbers() {
        return statementNumbersSet;
    }

    unordered_set<N> getAllStatementNodes() {
        return statementNodesSet;
    }



    virtual void clear() {
        statementNumbersSet.clear();
        statementNodesSet.clear();

        procedureNameToSetStatementNumbersMap.clear();
        statementNumberToProcedureNameMap.clear();
    }
};



