//
// Created by Lucas Tai on 18/3/22.
//

#ifndef SPA_SEMANTICSVERIFIER_H
#define SPA_SEMANTICSVERIFIER_H

#include "TNode/TNode.h"

class SemanticsVerifier {

public:
    static void detectCyclicCalls(Node* node);
    static void detectDuplicateProcedure(Node * node);
};


#endif //SPA_SEMANTICSVERIFIER_H
