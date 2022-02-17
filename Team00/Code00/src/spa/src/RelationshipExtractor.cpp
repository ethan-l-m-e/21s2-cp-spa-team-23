//
// Created by Tin Hong Wen on 4/2/22.
//
#include <iostream>

#include "RelationshipExtractor.h"
#include "PKB.h"
#include "TNode.h"
#include "Constants/Constants.h"

void RelationshipExtractor::extractFollows(Node * node) {
     /**
     * NOTE: Syntax of Tnode changed, so try to fix Tnode to work with the new Node(or nodes).
     */
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
                 cout<<(child -> getStmtNumber());
                 cout<<(nextChild -> getStmtNumber());
//                 pkb.setFollows(child -> getStmtNumber(), nextChild -> getStmtNumber());

                 // if child is if/while/procedure, perform recursion extractFollows(child)
                 /* might not need this but just gonna keep this first
                 if (string("procedure while if").find(child->getValue()) != string::npos) {
                     extractFollows(child);
                 }
                  */
             }
         }
         for (int i = 0; i < (numOfChildNodes); i++) {
             extractFollows(node->getStmtLst().at(i));
         }

     }
}

void RelationshipExtractor::extractParent(Node * node) {
    if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        for (int i = 0; i < (numOfChildNodes); i++) {
            Node *parent = node;
            Node *child = node->getStmtLst().at(i);
//            pkb.setParent(parent -> getStmtNumber(), child -> getStmtNumber());

        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i));
        }

    }
}

vector<string> RelationshipExtractor::extractUses (Node * node) {
    vector<string> varList = node->getListOfVarUsed();
    if (!varList.empty()) {
            pkb.createUses(node->getStmtNumber(), varList);
    }

    if(node->hasStmtLst()) {
        for (int i = 0; i < (node->getStmtLst().size()); i++) {
            extractUses(node->getStmtLst().at(i));
        }
    }
    // if node is assign/print statement
    //      search list of variables that is on the right side of node
    //      perform createUses(stmtNo, list of v)
    //      return list of v;
    // else if node is in while/procedure/call/if/while
    //      for each childNode in the node
    //          vector = extractUses(childNode)
    //          sum up all the vectors
    //      createUses(whatever, sum of all vectors)
    //      return list of v;
    // else return empty vector
    vector<string> v;
    return v;
}

vector<string> RelationshipExtractor::extractModifies (Node * node) {

    vector<string> varList = node->getListOfVarModified();
    if (!varList.empty()) {
//            pkb.createUses(node->getStmtNumber(), varList);
    }

    if(node->hasStmtLst()) {
        for (int i = 0; i < (node->getStmtLst().size()); i++) {
            extractModifies(node->getStmtLst().at(i));
        }
    }

    // if node is assign/print statement
    //      search list of variables that is on the right side of node
    //      perform createUses(stmtNo, list of v)
    //      return list of v;
    // else if node is in while/procedure/call/if
    //      for each childNode in the node
    //          vector = extractUses(childNode)
    //          sum up all the vectors
    //      createUses(whatever, sum of all vectors)
    //      return list of v;
    // else return empty vector
    vector<string> v;
    return v;
}

void RelationshipExtractor::extractRelationships(Node * node){
    extractFollows(node);
    extractParent(node);
    extractUses(node);
    extractModifies(node);
}

