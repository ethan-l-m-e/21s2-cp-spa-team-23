//
// Created by Karan Dev Sapra on 16/3/22.
//

#ifndef SPA_NEXTRELATIONSHIP_H
#define SPA_NEXTRELATIONSHIP_H

#import "OneToOneRelationship.h"
#import "TNode/CFG/NodeCFG.h"

class NextRelationship : OneToOneRelationship<int, NodeCFG *> {
public:
    void setRelationship(int lhs, NodeCFG *rhs);

    void clear();

    bool isNext(int previous, int next);

    unordered_map<int, NodeCFG *> getPreviousNodeOf(int next);

    int getNextNodeOf(int previous);

    // Functions below are used to calculate Next*

    NodeCFG* getCFGNode(int statementNumber);

    int getCFGSize();



};


#endif //SPA_NEXTRELATIONSHIP_H
