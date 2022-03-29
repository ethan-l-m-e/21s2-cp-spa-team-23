//
// Created by Karan Dev Sapra on 12/3/22.
//

#pragma once

#include<stdio.h>
#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBHelper.h"

using namespace std;

//class N;

template<class Node>
class StatementTable {


private:

    unordered_set<string> statementNumbersSet;
    unordered_set<Node> statementNodesSet;

public:


    void addStatement(Node node) {

        statementNumbersSet.insert(std::to_string(node->getStmtNumber()));
        statementNodesSet.insert(node);

    }


    bool isStatementNumber(string statementNumber) {
        return statementNumbersSet.find(statementNumber) != statementNumbersSet.end();
    }

    unordered_set<string> getAllStatementNumbers() {
        return statementNumbersSet;
    }

    unordered_set<Node> getAllStatementNodes() {
        return statementNodesSet;
    }



    void clear() {
        statementNumbersSet.clear();
        statementNodesSet.clear();
    }
};



