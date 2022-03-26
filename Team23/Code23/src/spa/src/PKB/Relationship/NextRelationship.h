//
// Created by Karan Dev Sapra on 16/3/22.
//

#ifndef SPA_NEXTRELATIONSHIP_H
#define SPA_NEXTRELATIONSHIP_H

#import "OneToOneRelationship.h"
#import "TNode/CFG/NodeCFG.h"

class NextRelationship : AbstractRelationship<int, int> {

    unordered_map<int, NodeCFG *> statementNumberToCfgNodeMap;

    void setRelationship(int lhs, int rhs) override {

    }; // This is private because we don't want anyone to call it

public:

    void addCFGNode(NodeCFG *node);


    void clear() override;

    bool isRelationship(string previousStatementNumber, string nextStatementNumber) override;

    unordered_set<string> getLHS(string nextStatementNumber) override;

    unordered_set<string> getRHS(string previousStatementNumber) override;

    // Functions below are used to calculate Next*

    NodeCFG* getCFGNode(string statementNumber);

    int getCFGSize();



};


#endif //SPA_NEXTRELATIONSHIP_H
