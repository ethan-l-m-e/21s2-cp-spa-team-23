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

using std::begin, std::end;

void extractFollowsFromStatementList(StatementList statementList) {
    int numOfChildNodes = statementList.size();
    if (numOfChildNodes > 1) {
        for (int i = 0; i < (numOfChildNodes - 1); i++) {
            Node *child = statementList.at(i);
            for (int j = i; j < numOfChildNodes - 1; j++) {
                Node *nextChild = statementList.at(j + 1);
                if (j == i) {
                    PKB::getInstance()->relationship.follows.setRelationship(child->getStmtNumber(), nextChild->getStmtNumber());
                }
                PKB::getInstance()->relationship.followsT.setRelationship(child->getStmtNumber(), nextChild->getStmtNumber());

            }
        }
    }
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
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractParent(p,parentList);

    }else if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        if(node->getStmtNumber()!=-1) {
            parentList.push_back((StmtLstNode *) node);
            Node *parent = node;
            for (int i = 0; i < (numOfChildNodes); i++) {
                Node *child = node->getStmtLst().at(i);
                PKB::getInstance()->relationship.parent.setRelationship(parent->getStmtNumber(), child->getStmtNumber());
                for (int j = 0; j < parentList.size(); j++) {
                    Node *parentT = parentList.at(j);
                    PKB::getInstance()->relationship.parentT.setRelationship(parentT->getStmtNumber(), child->getStmtNumber());
                }
            }
        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i), parentList);
        }
    }
}

//set all variables used by the node in the pkb
vector<string>  RelationshipExtractor::extractUses (Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractUses(p);

        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allUsedVariables, e;
        for(Node* s: stmtLst) {
            e = extractUses(s);
            allUsedVariables.insert(allUsedVariables.end(), e.begin(), e.end());
        }
        PKB::getInstance()->relationship.usesP.setRelationship(value->getProcName(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        //gather variables from cond_expr and stmtLst
        vector<VarName> condVariables = value->getCondExpr()->getListOfVarUsed();
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allUsedVariables;
        allUsedVariables.insert(allUsedVariables.end(), condVariables.begin(), condVariables.end());
        for(Node* stmt: stmtLst) {
            vector<VarName> usedVariables = extractUses(stmt);
            allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
        }
        PKB::getInstance()->relationship.usesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        vector<VarName> condVariables = value->getCondExpr()->getAllVariables();
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();
        vector<VarName> allUsedVariables;
        allUsedVariables.insert(allUsedVariables.end(), condVariables.begin(), condVariables.end());
        for(Node* stmt: elseVector) {
            vector<VarName> usedVariables = extractUses(stmt);
            allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
        }
        for(Node* stmt: thenVector) {
            vector<VarName> usedVariables = extractUses(stmt);
            allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
        }

        PKB::getInstance()->relationship.usesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getListOfVarUsed();
        PKB::getInstance()->relationship.usesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        vector<VarName> variables = value->getListOfVarUsed();
        PKB::getInstance()->relationship.usesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if (auto value = dynamic_cast<CallNode*>(node)) {
        Node* procedureCalled = value->getProcedure();
        vector<VarName> variables = extractUses(procedureCalled);
        PKB::getInstance()->relationship.usesS.setRelationship(value->getStmtNumber(),
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
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allModifiedVariables, e;
        for(Node* s: stmtLst) {
            e = extractModifies(s);
            allModifiedVariables.insert(allModifiedVariables.end(), e.begin(), e.end());
        }
        PKB::getInstance()->relationship.modifiesP.setRelationship(value->getProcName(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allModifiedVariables;
        for(Node* stmt: stmtLst) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        PKB::getInstance()->relationship.modifiesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();
        vector<VarName> allModifiedVariables;
        for(Node* stmt: elseVector) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        for(Node* stmt: thenVector) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        PKB::getInstance()->relationship.modifiesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getListOfVarModified();
        PKB::getInstance()->relationship.modifiesS.setRelationship(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if(auto value = dynamic_cast<ReadNode*>(node)) {
        vector<VarName> variables = value->getListOfVarModified();
        PKB::getInstance()->relationship.modifiesS.setRelationship(value->getStmtNumber(),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if (auto value = dynamic_cast<CallNode*>(node)) {
        Node* procedureCalled = value->getProcedure();
        vector<VarName> variables = extractModifies(procedureCalled);
        PKB::getInstance()->relationship.modifiesS.setRelationship(value->getStmtNumber(),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }
}
void RelationshipExtractor::extractCFG (Node * node) {
    auto value = dynamic_cast<ProgramNode *>(node);
    vector<ProcedureNode *> v = value->getProcLst();
    for (ProcedureNode *p: v) {
        vector<NodeCFG*> allCFGNodes = CFGConstructor::createCFG(p);
        for(NodeCFG* n : allCFGNodes){
            cout<<"\nnode stmt num: ";
            cout<<n->getStatementNumber();
            PKB::getInstance()->relationship.next.addCFGNode(n);
        }
    }
}
void RelationshipExtractor::extractRelationships(Node * node){
    vector<StmtLstNode*> v;
    extractFollows(node);
    extractParent(node,v);
    extractUses(node);
    extractModifies(node);
    extractCFG(node);
}

