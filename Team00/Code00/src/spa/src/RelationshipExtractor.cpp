//
// Created by Tin Hong Wen on 4/2/22.
//
#include <iostream>

#include "RelationshipExtractor.h"
#include "PKB.h"
#include "TNode.h"


void RelationshipExtractor::extractFollows(Node * node) {
    /**
     * NOTE: Syntax of Tnode changed, so try to fix Tnode to work with the new Node(or nodes).
     */
    /*
    if (node -> getNumberOfChildNodes() > 1) {
        for (int i = 0; i < (node -> getNumberOfChildNodes() - 1); i++) {
            TNode * child = node -> getNode(i);
            TNode * nextChild = node -> getNode(i+1);

            if (child -> hasStmtNo() && nextChild -> hasStmtNo()) {
                //pkb.setFollows(child -> getStmtNo(), nextChild -> getStmtNo());
            }
            // if child is if/while/procedure, perform recursion extractFollows(child)
            if (string("procedure while if").find(child -> getValue()) != string::npos) {
                extractFollows(child);
            }
        }
    }
     */
}

void RelationshipExtractor::extractParents(Node * node) {

}

vector<string> RelationshipExtractor::extractUses (Node * node) {
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

void RelationshipExtractor::extractRelationships(Node * node){
    extractFollows(node);
    extractParents(node);
    extractUses(node);
    extractModifies(node);
}

