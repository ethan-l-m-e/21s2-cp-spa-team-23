////
//// Created by Karan Dev Sapra on 12/3/22.
////
//
//#include<stdio.h>
//#include <unordered_set>
//
//#include "PKB/PKBHelper.h"
//
//#include "PKB/Statement-Old/AbstractStatement.h"
//
//#include "TNode/StmtNode.h"
//#include "TNode/AssignNode.h"
//#include "TNode/ReadNode.h"
//#include "TNode/PrintNode.h"
//#include "TNode/IfNode.h"
//#include "TNode/WhileNode.h"
//#include "TNode/CallNode.h"
//
//
//template<typename Alex>
//class AbstractSpecificStatement : AbstractStatement<Alex> {
//public:
//    StatementClass *statementClass;
//    AbstractSpecificStatement(StatementClass *statementClass);
//    void addStatement(Alex *node);
//};
//
//template<typename Alex>
//AbstractSpecificStatement<Alex>::AbstractSpecificStatement(StatementClass *statementClass) {
//    this->statementClass = statementClass;
//}
//
//template<typename Alex>
//void AbstractSpecificStatement<Alex>::addStatement(Alex *node) {
//
//    statementClass->addStatement(node);
//
//    this->statementNumbersSet.insert(node->getStmtNumber());
//    this->statementNodesSet.insert(node);
//
//}
//
//
//typedef AbstractSpecificStatement<AssignNode> AssignStatementClass;
//typedef AbstractSpecificStatement<ReadNode> ReadStatementClass;
//typedef AbstractSpecificStatement<PrintNode> PrintStatementClass;
//typedef AbstractSpecificStatement<IfNode> IfStatementClass;
//typedef AbstractSpecificStatement<WhileNode> WhileStatementClass;
//typedef AbstractSpecificStatement<CallNode> CallStatementClass;
