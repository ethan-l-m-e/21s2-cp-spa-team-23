//
// Created by Karan Dev Sapra on 12/3/22.
//

#include<stdio.h>
#include <unordered_set>

#include "PKB/PKBHelper.h"

#include "TNode/StmtNode.h"

using namespace std;

template<typename Alex>
class AbstractStatement {


private:
    AbstractStatement();

    unordered_set<int> statementNumbersSet;
    unordered_set<Alex *> statementNodesSet;

public:


    static AbstractStatement<Alex>* getInstance();

    void addStatement(Alex *node);

    unordered_set<string> getAllStatements();
};


// Templated methods and methods of templated classes must be defined in headers (with a couple hackish exceptions. (https://stackoverflow.com/questions/11452760/singleton-c-template-class)

using namespace std;

template<typename Alex>
AbstractStatement<Alex>::AbstractStatement() {

}

template<typename Alex>
void AbstractStatement<Alex>::addStatement(Alex *node) {

    statementNumbersSet.insert(node->getStmtNumber());
    statementNodesSet.insert(node);
}


template<typename Alex>
unordered_set<string> AbstractStatement<Alex>::getAllStatements() {
    return convertSetIntegersToSetStrings(statementNumbersSet);
}


typedef AbstractStatement<StmtNode> StatementClass;


#include "TNode/StmtNode.h"
#include "TNode/AssignNode.h"
#include "TNode/ReadNode.h"
#include "TNode/PrintNode.h"
#include "TNode/IfNode.h"
#include "TNode/WhileNode.h"
#include "TNode/CallNode.h"


template<typename Alex>
class AbstractSpecificStatement : AbstractStatement<Alex> {
public:
    StatementClass *statementClass;
    AbstractSpecificStatement(StatementClass *statementClass);
    void addStatement(Alex *node);
};

template<typename Alex>
AbstractSpecificStatement<Alex>::AbstractSpecificStatement(StatementClass *statementClass) {
    this->statementClass = statementClass;
}

template<typename Alex>
void AbstractSpecificStatement<Alex>::addStatement(Alex *node) {

    statementClass->addStatement(node);

    this->statementNumbersSet.insert(node->getStmtNumber());
    this->statementNodesSet.insert(node);

}


typedef AbstractSpecificStatement<AssignNode> AssignStatementClass;
typedef AbstractSpecificStatement<ReadNode> ReadStatementClass;
typedef AbstractSpecificStatement<PrintNode> PrintStatementClass;
typedef AbstractSpecificStatement<IfNode> IfStatementClass;
typedef AbstractSpecificStatement<WhileNode> WhileStatementClass;
typedef AbstractSpecificStatement<CallNode> CallStatementClass;
