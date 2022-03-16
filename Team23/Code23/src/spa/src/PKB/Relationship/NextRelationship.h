//
// Created by Karan Dev Sapra on 16/3/22.
//

#ifndef SPA_NEXTRELATIONSHIP_H
#define SPA_NEXTRELATIONSHIP_H

#import "OneToOneRelationship.h"
#import "TNode/CFG/NodeCFG.h"

class NextRelationship : OneToOneRelationship<int, NodeCFG *> {
    bool isNext(int previous, int next);

    unordered_map<int, NodeCFG *> getPreviousNodeOf(int next);

    NodeCFG* getNextNodeOf(int previous);

};


#endif //SPA_NEXTRELATIONSHIP_H
