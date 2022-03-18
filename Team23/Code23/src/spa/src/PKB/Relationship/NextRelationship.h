//
// Created by Karan Dev Sapra on 16/3/22.
//

#ifndef SPA_NEXTRELATIONSHIP_H
#define SPA_NEXTRELATIONSHIP_H

#import "OneToOneRelationship.h"
#import "TNode/CFG/NodeCFG.h"

class NextRelationship : OneToOneRelationship<int, NodeCFG *> {
public:

    void addCFGNode(NodeCFG *node);


    void clear();

    bool isNext(string previousStatementNumber, string nextStatementNumber);

    unordered_set<string> getPreviousNodeOf(string nextStatementNumber);

    unordered_set<string> getNextNodeOf(string previousStatementNumber);

    // Functions below are used to calculate Next*

    NodeCFG* getCFGNode(string statementNumber);

    int getCFGSize();



};


#endif //SPA_NEXTRELATIONSHIP_H
