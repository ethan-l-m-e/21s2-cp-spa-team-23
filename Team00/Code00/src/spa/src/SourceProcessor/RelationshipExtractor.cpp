//
// Created by Tin Hong Wen on 4/2/22.
//
#include <iostream>

#include "RelationshipExtractor.h"
#include "PKB.h"
#include "TNode.h"
#include "Constants/Constants.h"
#include <unordered_set>

//extracts all follows relationship starting from given node
void RelationshipExtractor::extractFollows(Node * node) {
     if(node->hasStmtLst()) {
         int numOfChildNodes = node->getStmtLst().size();
         if (numOfChildNodes > 1) {
             for (int i = 0; i < (numOfChildNodes - 1); i++) {
                 Node *child = node->getStmtLst().at(i);
                 for(int j = i; j<numOfChildNodes-1;j++){
                     Node *nextChild = node->getStmtLst().at(j + 1);
                    if(j==i) {
                        PKB::getInstance()->setFollows(child->getStmtNumber(), nextChild->getStmtNumber());
                    }
                     PKB::getInstance()->setFollowsT(child->getStmtNumber(), nextChild->getStmtNumber());

                 }
             }
         }
         for (int i = 0; i < (numOfChildNodes); i++) {
             extractFollows(node->getStmtLst().at(i));
         }
     }
}
//extracts all parents relationship starting from given node
void RelationshipExtractor::extractParent(Node * node, vector<StmtLstNode*> parentList) {
    if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        if(node->getStmtNumber()!=-1) {
            parentList.push_back((StmtLstNode *) node);
            Node *parent = node;
            for (int i = 0; i < (numOfChildNodes); i++) {
                Node *child = node->getStmtLst().at(i);
                PKB::getInstance()->setParent(parent->getStmtNumber(), child->getStmtNumber());
                for (int j = 0; j < parentList.size(); j++) {
                    Node *parentT = parentList.at(j);
                    PKB::getInstance()->setParentT(parentT->getStmtNumber(), child->getStmtNumber());
                }
            }
        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i), parentList);
        }
    }
}
//set all variables used by the node in the pkb
void RelationshipExtractor::extractUses (Node * node) {
    vector<string> varList = node->getListOfVarUsed();
    if (!varList.empty()) {

        std::unordered_set<string> set;
        for (string &i: varList) {
            set.insert(i);
        }

        PKB::getInstance()->setUses(node->getStmtNumber(),set);
    }

    if(node->hasStmtLst()) {
        for (int i = 0; i < (node->getStmtLst().size()); i++) {
            extractUses(node->getStmtLst().at(i));
        }
    }
}

//set all variables modified by the node in the pkb
void RelationshipExtractor::extractModifies (Node * node) {

    vector<string> varList = node->getListOfVarModified();
    if (!varList.empty()) {
        std::unordered_set<string> set;
        for (string &i: varList) {
            set.insert(i);
        }
        PKB::getInstance()->setModifies(node->getStmtNumber(),set);
    }

    if(node->hasStmtLst()) {
        for (int i = 0; i < (node->getStmtLst().size()); i++) {
            extractModifies(node->getStmtLst().at(i));
        }
    }
}

void extractAllVariables(Node *node) {
    vector<string> list;
    list = node->getAllVariables();
    for(string variable: list) {
        cout << "sending var " << variable << " to PKB\n";
        PKB::getInstance() ->addVariable(variable);
    }
}

void extractAllConstant(Node *node) {
    vector<string> list;
    list = node->getAllConstants();
    for(string constant: list) {
        cout << "sending const " << constant << " to PKB\n";
        PKB::getInstance() ->addConstant(constant);
    }
}

void extractAllReadStmt(Node *node) {
    vector<stmtNo> list;
    list = node->getAllReadStmt();
    for(int num: list) {
        cout << "sending read " << num << " to PKB\n";
        PKB::getInstance()->addReadStatement(num);
    }
}

void extractAllPrintStmt(Node *node) {
    vector<stmtNo> list;
    list = node->getAllPrintStmt();
    for(int num: list) {
        cout << "sending print " << num << " to PKB\n";
        PKB::getInstance()->addPrintStatement(num);
    }
}

void extractAllAssignStmt(Node *node) {
    vector<stmtNo> list;
    list = node->getAllAssignStmt();
    for(int num: list) {
        cout << "sending assign " << num << " to PKB\n";
        PKB::getInstance()->addAssignStatement(num);
    }
}

void extractAllAssignNodes(Node *node) {
    vector<AssignNode*> list;
    list = node-> getAllAssignNodes();
    for(AssignNode* a: list) {
        cout << "assign pointers " << to_string(a->getStmtNumber()) << "\n";
        PKB::getInstance()->addAssignNode(a);
    }
}

void RelationshipExtractor::extractRelationships(Node * node){
    //extract relationship
    vector<StmtLstNode*> v;
    extractFollows(node);
    extractParent(node,v);
    extractUses(node);
    extractModifies(node);

    //extract entities
    extractAllVariables(node);
    extractAllConstant(node);
    extractAllReadStmt(node);
    extractAllPrintStmt(node);
    extractAllAssignStmt(node);
    extractAllAssignNodes(node);

}

