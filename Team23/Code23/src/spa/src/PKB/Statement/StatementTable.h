//
// Created by Karan Dev Sapra on 12/3/22.
//

#pragma once

#include<stdio.h>
#include <unordered_set>

#include "PKB/PKBHelper.h"

using namespace std;

//class N;

template<class Node>
class StatementTable {


private:

    unordered_set<int> statementNumbersSet;
    unordered_set<Node> statementNodesSet;

public:

    StatementTable() {

    }

    void addStatement(Node node) {

        statementNumbersSet.insert(node->getStmtNumber());
        statementNodesSet.insert(node);
    }

    bool isStatementNumber(int statementNumber) {
        return statementNumbersSet.find(statementNumber) != statementNumbersSet.end();
    }
    bool isStatementNumber(string statementNumber) {
        return isStatementNumber(std::stoi(statementNumber));
    }

    unordered_set<string> getAllStatementNumbers() {
        return convertSetGenericsToSetStrings(statementNumbersSet);
    }

    unordered_set<Node> getAllStatementNodes() {
        return statementNodesSet;
    }



    void clear() {
        statementNumbersSet.clear();
        statementNodesSet.clear();
    }
};



