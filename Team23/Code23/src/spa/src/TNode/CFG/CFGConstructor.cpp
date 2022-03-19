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
 * returns new CFGNode(s) created in a vector
 */
vector<NodeCFG*> CFGConstructor::populateCFG(Node* currNode, vector<NodeCFG*> prevSetOfNodes,vector<NodeCFG*>* setOfAllNodes) {
    vector<NodeCFG*> newSetOfNodes;
    if(auto value = dynamic_cast<WhileNode*>(currNode)) {
        auto* newCFGNode = new LoopCFG(currNode->getStmtNumber());
        if (!prevSetOfNodes.empty()) {
            for (NodeCFG *s: prevSetOfNodes) {
                newCFGNode->setAllPreviousNodes(s->getAllPreviousNode());
                s->setNextNode(newCFGNode);
            }
        }

        vector<Node *> stmtLst = value->getStmtLst();
        newSetOfNodes.push_back(newCFGNode);
        bool isFirstLoop = true;
        vector<NodeCFG*> nextSetOfNodes;

        for (Node *s: stmtLst) {
            if(isFirstLoop){
                nextSetOfNodes = populateCFG(s,newSetOfNodes,setOfAllNodes );
                newCFGNode->setNodeInLoop(nextSetOfNodes.at(0));
                isFirstLoop = false;
            }else{
                nextSetOfNodes = populateCFG(s,nextSetOfNodes,setOfAllNodes );
            }
        }
        //last node in while loop to point towards initial LoopCFG
        nextSetOfNodes.at(0)->setNextNode(newCFGNode);
        for(NodeCFG* n : newSetOfNodes) {
            setOfAllNodes->push_back(n);
        }

    }else if(auto value = dynamic_cast<IfNode*>(currNode)) {
        auto* newCFGNode = new BranchCFG(currNode->getStmtNumber());
        if (!prevSetOfNodes.empty()) {
            for (NodeCFG *s: prevSetOfNodes) {
                newCFGNode->setAllPreviousNodes(s->getAllPreviousNode());
                s->setNextNode(newCFGNode);
            }
        }

        vector<Node *> thenBranch = value->getThenStmtLst();
        vector<Node *> elseBranch = value->getElseStmtLst();
        vector<NodeCFG*> currSetOfNodes;
        currSetOfNodes.push_back(newCFGNode);
        vector<NodeCFG*> nextSetOfNodes1;

        bool isThenBranchFirstLoop = true;
        for (Node *s: thenBranch) {
            if(isThenBranchFirstLoop){
                nextSetOfNodes1 = populateCFG(s,currSetOfNodes,setOfAllNodes );
                for (NodeCFG *t: nextSetOfNodes1) {
                    newCFGNode->setLeftNode(t);
                }
                isThenBranchFirstLoop = false;
            }else{
                nextSetOfNodes1 = populateCFG(s,nextSetOfNodes1,setOfAllNodes );
            }
        }
        vector<NodeCFG*> nextSetOfNodes2;
        bool isElseBranchFirstLoop = true;
        for (Node *s: elseBranch) {
            if(isElseBranchFirstLoop){
                nextSetOfNodes2 = populateCFG(s,currSetOfNodes,setOfAllNodes );
                for (NodeCFG *t: nextSetOfNodes2) {
                    newCFGNode->setRightNode(t);
                }
                isElseBranchFirstLoop = false;
            }else{
                nextSetOfNodes2 = populateCFG(s,nextSetOfNodes2,setOfAllNodes );
            }
        }
        for (NodeCFG *t: nextSetOfNodes1) {
            newSetOfNodes.push_back(t);
        }
        for (NodeCFG *t: nextSetOfNodes2) {
            newSetOfNodes.push_back(t);
        }
        setOfAllNodes->push_back(newCFGNode);
    }else{
        auto* newCFGNode = new NodeCFG(currNode->getStmtNumber());
        if (!prevSetOfNodes.empty()) {
            for (NodeCFG *s: prevSetOfNodes) {
                newCFGNode->setAllPreviousNodes(s->getAllPreviousNode());
                s->setNextNode(newCFGNode);
            }
        }
        newSetOfNodes.push_back(newCFGNode);
        for(NodeCFG* n : newSetOfNodes) {
            setOfAllNodes->push_back(n);
        }

    }
    return newSetOfNodes;
}

