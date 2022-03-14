//
// Created by Karan Dev Sapra on 12/3/22.
//

#pragma once

#include "GenericStatement.h"

#include "PKB/Statement/GenericStatement.h"

class StmtNode;

template<class Node>
class GenericSpecificStatement : public GenericStatement<StmtNode> {

    GenericStatement<StmtNode> *standardStatementClass;

public:
    explicit GenericSpecificStatement(GenericStatement<StmtNode> *statementClass) {
        this->standardStatementClass = statementClass;
    }

    void addStatement(Node *node) {
        this->standardStatementClass->addStatement(node);

        this->addStatement(node);
    }


};


