//
// Created by Lucas Tai on 12/3/22.
//

#include "CFGConstructor.h"
#include "NodeCFG.h"
#include "TNode/WhileNode.h"
#include "TNode/IfNode.h"
#include "iostream"
vector<NodeCFG*> CFGConstructor::createCFG(ProcedureNode* p) {
    vector<Node*> stmtLst = p->getStmtLst();
    unordered_map<int, NodeCFG *> currMapOfPrevNodes;
    vector<NodeCFG*> prevNode;
    vector<NodeCFG*> setOfAllNodes;
    for(Node* s: stmtLst) {
        prevNode = CFGConstructor::populateCFG(s, prevNode,&setOfAllNodes);
    }
    return setOfAllNodes;
}

/*
 * returns new CFGNode(s) created in a vector with the use of recursion
 */
vector<NodeCFG*> CFGConstructor::populateCFG(Node* currNode, vector<NodeCFG*> prevSetOfNodes,vector<NodeCFG*>* setOfAllNodes) {
    vector<NodeCFG*> newSetOfNodes;
    if(auto value = dynamic_cast<WhileNode*>(currNode)) {
        auto* newCFGNode = new LoopCFG(currNode->getStmtNumber());

        setNextNodeOfPrevSetOfNodes(newCFGNode,prevSetOfNodes);

        vector<Node *> stmtLst = value->getStmtLst();
        newSetOfNodes.push_back(newCFGNode);

        populateCFGInWhileLoop(newCFGNode,stmtLst,setOfAllNodes);

        for(NodeCFG* n : newSetOfNodes) {
            setOfAllNodes->push_back(n);
        }

    }else if(auto value = dynamic_cast<IfNode*>(currNode)) {
        auto* newCFGNode = new BranchCFG(currNode->getStmtNumber());

        setNextNodeOfPrevSetOfNodes(newCFGNode,prevSetOfNodes);

        vector<Node *> thenBranch = value->getThenStmtLst();
        vector<Node *> elseBranch = value->getElseStmtLst();

        newSetOfNodes = populateCFGInBranchNode(newCFGNode,thenBranch,elseBranch,setOfAllNodes);

        setOfAllNodes->push_back(newCFGNode);
    }else{
        auto* newCFGNode = new NodeCFG(currNode->getStmtNumber());

        setNextNodeOfPrevSetOfNodes(newCFGNode,prevSetOfNodes);

        newSetOfNodes.push_back(newCFGNode);
        for(NodeCFG* n : newSetOfNodes) {
            setOfAllNodes->push_back(n);
        }

    }
    return newSetOfNodes;
}

void CFGConstructor::setNextNodeOfPrevSetOfNodes(NodeCFG* currNode, vector<NodeCFG*> prevSetOfNodes){
    if (!prevSetOfNodes.empty()) {
        for (NodeCFG *s: prevSetOfNodes) {
            s->setNextNode(currNode);
        }
    }
}

void CFGConstructor::populateCFGInWhileLoop(LoopCFG* initNode, vector<Node *> stmtLst,vector<NodeCFG*>* setOfAllNodes){
    vector<NodeCFG*> nextSetOfNodes;
    bool isFirstLoop = true;
    for (Node *s: stmtLst) {
        nextSetOfNodes = CFGConstructor::populateCFG(s,nextSetOfNodes,setOfAllNodes );

        if(isFirstLoop){
            initNode->setNodeInLoop(nextSetOfNodes.at(0));
            isFirstLoop = false;
        }
    }
    //last node in while loop to point towards initial LoopCFG
    for(NodeCFG* n : nextSetOfNodes) {
        n->setNextNode(initNode);
    }
}
vector<NodeCFG*> CFGConstructor::populateCFGInBranchNode(BranchCFG* initNode, vector<Node *> thenBranch,vector<Node *> elseBranch,vector<NodeCFG*>* setOfAllNodes){
    vector<NodeCFG*> currSetOfNodes;
    currSetOfNodes.push_back(initNode);
    vector<NodeCFG*> nextSetOfNodes1;
    vector<NodeCFG*> newSetOfNodes;

    bool isThenBranchFirstLoop = true;
    for (Node *s: thenBranch) {
        if(isThenBranchFirstLoop){
            nextSetOfNodes1 = CFGConstructor::populateCFG(s,currSetOfNodes,setOfAllNodes );
            for (NodeCFG *t: nextSetOfNodes1) {initNode->setLeftNode(t);}
            isThenBranchFirstLoop = false;
        }else{
            nextSetOfNodes1 = CFGConstructor::populateCFG(s,nextSetOfNodes1,setOfAllNodes );
        }
    }
    vector<NodeCFG*> nextSetOfNodes2;
    bool isElseBranchFirstLoop = true;
    for (Node *s: elseBranch) {
        if(isElseBranchFirstLoop){
            nextSetOfNodes2 = CFGConstructor::populateCFG(s,currSetOfNodes,setOfAllNodes );
            for (NodeCFG *t: nextSetOfNodes2) {initNode->setRightNode(t);}
            isElseBranchFirstLoop = false;
        }else{
            nextSetOfNodes2 = CFGConstructor::populateCFG(s,nextSetOfNodes2,setOfAllNodes );
        }
    }
    for (NodeCFG *t: nextSetOfNodes1) {
        newSetOfNodes.push_back(t);
    }
    for (NodeCFG *t: nextSetOfNodes2) {
        newSetOfNodes.push_back(t);
    }
    return newSetOfNodes;
}