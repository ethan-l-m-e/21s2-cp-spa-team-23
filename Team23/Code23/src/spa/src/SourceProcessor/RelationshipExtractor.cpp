//
// Created by Tin Hong Wen on 4/2/22.
//
#include "RelationshipExtractor.h"
#include "PKB/PKB.h"
#include "TNode/Node.h"
#include "TNode/ProgramNode.h"
#include "TNode/AssignNode.h"
#include "TNode/WhileNode.h"
#include "TNode/IfNode.h"
#include "TNode/ReadNode.h"
#include "TNode/PrintNode.h"
#include "TNode/CallNode.h"
#include "TNode/CFG/CFGConstructor.h"
#include <unordered_set>

void setFollowsInPkb(int i, int i1, StatementList vector1);

using std::begin, std::end;

void extractFollowsFromStatementList(StatementList statementList) {
    int numOfChildNodes = statementList.size();
    if (numOfChildNodes > 1) {
        for (int i = 0; i < (numOfChildNodes - 1); i++) {
            Node *child = statementList.at(i);
            setFollowsInPkb(i, numOfChildNodes - 1, statementList);
        }
    }
}

void setFollowsInPkb(int start, int end, StatementList statementList) {
    Node *child = statementList.at(start);
    for (int i = start; i < end; i++) {
        Node *nextChild = statementList.at(i + 1);
        if (i == start) {
            PKB::getInstance()->relationship.follows.setRelationship(std::to_string(child->getStmtNumber()), std::to_string(nextChild->getStmtNumber()));
        }
        PKB::getInstance()->relationship.followsT.setRelationship(std::to_string(child->getStmtNumber()), std::to_string(nextChild->getStmtNumber()));
    }
}

void extractParentFromParentList(Node *parent, vector<StmtLstNode*> parentList, StatementList statementList) {
    int numOfChildNodes = statementList.size();
    for (int i = 0; i < (numOfChildNodes); i++) {
        Node *child = statementList.at(i);
        PKB::getInstance()->relationship.parent.setRelationship(std::to_string(parent->getStmtNumber()), std::to_string(child->getStmtNumber()));
        for (int j = 0; j < parentList.size(); j++) {
            Node *parentT = parentList.at(j);
            PKB::getInstance()->relationship.parentT.setRelationship(std::to_string(parentT->getStmtNumber()), std::to_string(child->getStmtNumber()));
        }
    }
}

vector<VarName> extractUsesFromProcedureNode(ProcedureNode* value) {
    vector<Node*> stmtLst = value->getStmtLst();
    vector<VarName> allUsedVariables, e;
    for(Node* s: stmtLst) {
        e = RelationshipExtractor::extractUses(s);
        allUsedVariables.insert(allUsedVariables.end(), e.begin(), e.end());
    }
    PKB::getInstance()->relationship.usesP.setRelationship(value->getProcName(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
    return allUsedVariables;
}

vector<VarName> extractUsesFromWhileNode(WhileNode* value) {
    //gather variables from cond_expr and stmtLst
    vector<VarName> condVariables = value->getCondExpr()->getListOfVarUsed();
    vector<Node*> stmtLst = value->getStmtLst();
    vector<VarName> allUsedVariables;
    allUsedVariables.insert(allUsedVariables.end(), condVariables.begin(), condVariables.end());
    for(Node* stmt: stmtLst) {
        vector<VarName> usedVariables = RelationshipExtractor::extractUses(stmt);
        allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
    }
    PKB::getInstance()->relationship.usesS.setRelationship(std::to_string(value->getStmtNumber()), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
    return allUsedVariables;
}

vector<VarName> extractUsesFromIfNode(IfNode* value) {
    vector<VarName> condVariables = value->getCondExpr()->getAllVariables();
    vector<Node*> elseVector = value->getElseStmtLst();
    vector<Node*> thenVector = value->getThenStmtLst();
    vector<VarName> allUsedVariables;
    allUsedVariables.insert(allUsedVariables.end(), condVariables.begin(), condVariables.end());
    for(Node* stmt: elseVector) {
        vector<VarName> usedVariables = RelationshipExtractor::extractUses(stmt);
        allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
    }
    for(Node* stmt: thenVector) {
        vector<VarName> usedVariables = RelationshipExtractor::extractUses(stmt);
        allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
    }

    PKB::getInstance()->relationship.usesS.setRelationship(std::to_string(value->getStmtNumber()), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
    return allUsedVariables;
}

vector<VarName> extractUsesFromAssignPrintNode(Node * node) {
    vector<VarName> variables = node->getListOfVarUsed();
    PKB::getInstance()->relationship.usesS.setRelationship(std::to_string(node->getStmtNumber()), unordered_set<VarName>{variables.begin(), variables.end()});
    return variables;
}

vector<VarName> extractModifiesFromProcedureNode(ProcedureNode* value) {
    vector<Node*> stmtLst = value->getStmtLst();
    vector<VarName> allModifiedVariables, e;
    for(Node* s: stmtLst) {
        e = RelationshipExtractor::extractModifies(s);
        allModifiedVariables.insert(allModifiedVariables.end(), e.begin(), e.end());
    }
    PKB::getInstance()->relationship.modifiesP.setRelationship(value->getProcName(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
    return allModifiedVariables;
}

vector<VarName> extractModifiesFromWhileNode(WhileNode* value) {
    vector<Node*> stmtLst = value->getStmtLst();
    vector<VarName> allModifiedVariables;
    for(Node* stmt: stmtLst) {
        vector<VarName> modifiedVariables = RelationshipExtractor::extractModifies(stmt);
        allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
    }
    PKB::getInstance()->relationship.modifiesS.setRelationship(std::to_string(value->getStmtNumber()), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
    return allModifiedVariables;
}

vector<VarName> extractModifiesFromIfNode(IfNode* value) {
    vector<Node*> elseVector = value->getElseStmtLst();
    vector<Node*> thenVector = value->getThenStmtLst();
    vector<VarName> allModifiedVariables;
    for(Node* stmt: elseVector) {
        vector<VarName> modifiedVariables = RelationshipExtractor::extractModifies(stmt);
        allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
    }
    for(Node* stmt: thenVector) {
        vector<VarName> modifiedVariables = RelationshipExtractor::extractModifies(stmt);
        allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
    }
    PKB::getInstance()->relationship.modifiesS.setRelationship(std::to_string(value->getStmtNumber()), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
    return allModifiedVariables;
}

vector<VarName> extractModifiesFromAssignReadNode(Node* value) {
    vector<VarName> variables = value->getListOfVarModified();
    PKB::getInstance()->relationship.modifiesS.setRelationship(std::to_string(value->getStmtNumber()), unordered_set<VarName>{variables.begin(), variables.end()});
    return variables;
}

void RelationshipExtractor::extractFollows(Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractFollows(p);
    } else if (auto value = dynamic_cast<ProcedureNode*>(node)) {
        StatementList statementList = value->getStmtLst();
        extractFollowsFromStatementList(statementList);
        for(Node* node: statementList)
            extractFollows(node);
    } else if (auto value = dynamic_cast<WhileNode*>(node)) {
        StatementList statementList = value->getStmtLst();
        extractFollowsFromStatementList(statementList);
        for(Node* node: statementList)
            extractFollows(node);
    } else if (auto value = dynamic_cast<IfNode*>(node)) {
        StatementList elseStatementList = value->getElseStmtLst();
        extractFollowsFromStatementList(elseStatementList);
        StatementList thenStatementList = value->getThenStmtLst();
        extractFollowsFromStatementList(thenStatementList);
        for(Node* node: elseStatementList)
            extractFollows(node);
        for(Node* node: thenStatementList)
            extractFollows(node);
    }
}


//extracts all parents relationship starting from given node
void RelationshipExtractor::extractParent(Node * node, vector<StmtLstNode*> parentList) {
    if (auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractParent(p,parentList);

    } else if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        if(node->getStmtNumber()!=-1) {
            parentList.push_back((StmtLstNode *) node);
            Node *parent = node;
            extractParentFromParentList(parent, parentList, node->getStmtLst());
        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i), parentList);
        }
    }
}

//set all variables used by the node in the pkb
vector<string>  RelationshipExtractor::extractUses (Node * node) {
    if (auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractUses(p);
        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        return extractUsesFromProcedureNode(value);
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        return extractUsesFromWhileNode(value);
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        return extractUsesFromIfNode(value);
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        return extractUsesFromAssignPrintNode(value);
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        return extractUsesFromAssignPrintNode(value);
    } else if (auto value = dynamic_cast<CallNode*>(node)) {
        Node* procedureCalled = value->getProcedure();
        vector<VarName> variables = extractUses(procedureCalled);
        PKB::getInstance()->relationship.usesS.setRelationship(std::to_string(value->getStmtNumber()),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }


}

//set all variables modified by the node in the pkb
vector<string> RelationshipExtractor::extractModifies (Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractModifies(p);

        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        return extractModifiesFromProcedureNode(value);
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        return extractModifiesFromWhileNode(value);
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        return extractModifiesFromIfNode(value);
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        return extractModifiesFromAssignReadNode(node);
    } else if(auto value = dynamic_cast<ReadNode*>(node)) {
        return extractModifiesFromAssignReadNode(node);
    } else if (auto value = dynamic_cast<CallNode*>(node)) {
        Node* procedureCalled = value->getProcedure();
        vector<VarName> variables = extractModifies(procedureCalled);
        PKB::getInstance()->relationship.modifiesS.setRelationship(std::to_string(value->getStmtNumber()),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }
}

void RelationshipExtractor::extractCalls(Node* node, vector<ProcedureNode *> procList,ProcedureNode* latestProc) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v) {
            vector<ProcedureNode *> currProcList;
            currProcList.push_back(p);
            extractCalls(p, currProcList, p);
        }
    }else if (auto value = dynamic_cast<CallNode*>(node)){
        ProcName calledProc = value->getProcName();
        if(latestProc != nullptr){
            PKB::getInstance()->relationship.calls.setRelationship(latestProc->getProcName(),calledProc);
        }
        for (ProcedureNode *p: procList) {
            PKB::getInstance()->relationship.callsT.setRelationship(p->getProcName(), calledProc);
        }
        procList.push_back(dynamic_cast<ProcedureNode*>(value->getProcedure()));
        extractCalls(value->getProcedure(), procList, nullptr);
    }else if(node->hasStmtLst()) {
        for (Node *p: node->getStmtLst()) {
            extractCalls(p, procList, latestProc);
        }
    }
}


void RelationshipExtractor::extractCFG (Node * node) {
    auto value = dynamic_cast<ProgramNode *>(node);
    vector<ProcedureNode *> v = value->getProcLst();
    for (ProcedureNode *p: v) {
        vector<NodeCFG*> allCFGNodes = CFGConstructor::createCFG(p);
        for(NodeCFG* n : allCFGNodes){
            PKB::getInstance()->relationship.next.addCFGNode(n);
        }
    }
}
void RelationshipExtractor::extractRelationships(Node * node){
    vector<StmtLstNode*> v;
    vector<ProcedureNode *> procList;
    extractFollows(node);
    extractParent(node,v);
    extractUses(node);
    extractModifies(node);
    extractCalls(node,procList,nullptr);
    extractCFG(node);
}

