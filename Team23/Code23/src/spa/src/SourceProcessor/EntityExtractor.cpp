//
// Created by Lucas Tai on 18/3/22.
//

#include "EntityExtractor.h"
#include "PKB/PKB.h"

void EntityExtractor::extractAllEntities(Node *node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractAllEntities(p);
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> v = value->getStmtLst();
        for(Node* s: v) {
            extractAllEntities(s);
        }
        PKB::getInstance()->entity.procedures.add(value->getProcName());
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        Node* condExprNode = value->getCondExpr();
        vector<VarName> variables = condExprNode->getAllVariables();
        vector<Constant> constants = condExprNode->getAllConstants();
        vector<Node*> stmtLst = value->getStmtLst();
        for(VarName v: variables)
            PKB::getInstance()->entity.variables.add(v);
        for(Constant c: constants)
            PKB::getInstance()->entity.constants.add(c);
        for(Node* s: stmtLst)
            extractAllEntities(s);
        PKB::getInstance()->statement.statements.addStatement(value);
        PKB::getInstance()->statement.whileStatements.addStatement(value);
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        Node* condExprNode = value->getCondExpr();
        vector<VarName> variables = condExprNode->getAllVariables();
        vector<Constant> constants = condExprNode->getAllConstants();
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();
        for(VarName v: variables)
            PKB::getInstance()->entity.variables.add(v);
        for(Constant c: constants)
            PKB::getInstance()->entity.constants.add(c);
        for(Node* s: elseVector)
            extractAllEntities(s);
        for(Node* s: thenVector)
            extractAllEntities(s);
        PKB::getInstance()->statement.statements.addStatement(value);
        PKB::getInstance()->statement.ifStatements.addStatement(value);
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getAllVariables();
        vector<Constant> constants = value->getAllConstants();
        for(VarName variable: variables ) {
            PKB::getInstance() ->entity.variables.add(variable);
        }
        for(Constant constant: constants) {
            PKB::getInstance() ->entity.constants.add(constant);
        }
        PKB::getInstance()->statement.statements.addStatement(value);
        PKB::getInstance()->statement.assignStatements.addStatement(value);
    } else if(auto value = dynamic_cast<CondExprNode*>(node)) {
        vector<VarName> variables = value->getAllVariables();
        vector<Constant> constants = value->getAllConstants();
        for(VarName variable: variables ) {
            PKB::getInstance() ->entity.variables.add(variable);
        }
        for(Constant constant: constants) {
            PKB::getInstance() ->entity.constants.add(constant);
        }
    } else if(auto value = dynamic_cast<ReadNode*>(node)) {
        PKB::getInstance()->statement.statements.addStatement(value);
        PKB::getInstance()->statement.readStatements.addStatement(value);
        PKB::getInstance()->entity.variables.add(value->getVarName());
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        PKB::getInstance()->statement.statements.addStatement(value);
        PKB::getInstance()->statement.printStatements.addStatement(value);
        PKB::getInstance()->entity.variables.add(value->getVarName());
    } else if(auto value = dynamic_cast<CallNode*>(node)) {
        PKB::getInstance()->statement.statements.addStatement(value);
        PKB::getInstance()->statement.callStatements.addStatement(value);
        PKB::getInstance()->entity.procedures.add(value->getProcName());//Not sure if needed
    }
}
void EntityExtractor::assignProcedureToNodes(Node* node, ProcedureNode* proc){
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            assignProcedureToNodes(p,nullptr);
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> v = value->getStmtLst();
        for(Node* s: v) {
            assignProcedureToNodes(s,value);
        }
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        value->setProc(proc);
        vector<Node*> stmtLst = value->getStmtLst();
        for(Node* s: stmtLst)
            assignProcedureToNodes(s,proc);
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        value->setProc(proc);
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();

        for(Node* s: elseVector)
            assignProcedureToNodes(s,proc);
        for(Node* s: thenVector)
            assignProcedureToNodes(s,proc);
    } else if(auto value = dynamic_cast<StmtNode*>(node)){
        value->setProc(proc);
    }
}