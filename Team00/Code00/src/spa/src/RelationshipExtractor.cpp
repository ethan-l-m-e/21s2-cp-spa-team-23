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
     cout<<"outer\n";
     cout<<node->getStmtNumber();
     if(node->hasStmtLst()) {
         int numOfChildNodes = node->getStmtLst().size();
         cout<<(node->getStmtLst().size());
         if (numOfChildNodes > 1) {
             cout<<"second if\n";
             for (int i = 0; i < (numOfChildNodes - 1); i++) {
                 cout<<"for loop\n";
                 Node *child = node->getStmtLst().at(i);
                 Node *nextChild = node->getStmtLst().at(i + 1);
                 PKB::getInstance()->setFollows(child->getStmtNumber(),nextChild -> getStmtNumber());
                 cout<<(child -> getStmtNumber());
                 cout<<(nextChild -> getStmtNumber());

             }
         }
         for (int i = 0; i < (numOfChildNodes); i++) {
             extractFollows(node->getStmtLst().at(i));
         }
     }
}
//extracts all parents relationship starting from given node
void RelationshipExtractor::extractParent(Node * node) {
    if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        for (int i = 0; i < (numOfChildNodes); i++) {
            Node *parent = node;
            Node *child = node->getStmtLst().at(i);
            PKB::getInstance()->setParent(parent->getStmtNumber(),child -> getStmtNumber());

        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i));
        }

    }
}

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

void RelationshipExtractor::extractRelationships(Node * node){
    extractFollows(node);
    extractParent(node);
    extractUses(node);
    extractModifies(node);
}

