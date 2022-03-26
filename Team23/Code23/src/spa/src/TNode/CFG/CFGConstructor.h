//
// Created by Lucas Tai on 12/3/22.
//

#ifndef SPA_CFGCONSTRUCTOR_H
#define SPA_CFGCONSTRUCTOR_H
#include "NodeCFG.h"
#include "TNode/ProcedureNode.h"

class CFGConstructor {

public:
    static vector<NodeCFG *> createCFG(ProcedureNode *p);

    static vector<NodeCFG *> populateCFG(Node *, vector<NodeCFG *>, vector<NodeCFG *> *);

    static void setNextNodeOfPrevSetOfNodes(NodeCFG *, vector<NodeCFG *>);

    static void populateCFGInWhileLoop(LoopCFG *initNode, vector<Node *> stmtLst, vector<NodeCFG *> *setOfAllNodes);

    static vector<NodeCFG*> populateCFGInBranchNode(BranchCFG* initNode, vector<Node *> thenBranch,vector<Node *> elseBranch,vector<NodeCFG*>* setOfAllNodes);

};
#endif //SPA_CFGCONSTRUCTOR_H
