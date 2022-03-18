//
// Created by Lucas Tai on 12/3/22.
//

#include "CFGConstructor.h"
#include "NodeCFG.h"
#include "TNode/WhileNode.h"
#include "TNode/IfNode.h"
#include "iostream"

NodeCFG* CFGConstructor::createCFG(ProcedureNode p) {
    vector<Node*> stmtLst = p.getStmtLst();
    unordered_map<int, NodeCFG *> currMapOfPrevNodes;
    vector<NodeCFG*> prevNode;
    vector<NodeCFG*> firstSetOfNodes;
    NodeCFG* firstNode;
    bool isFirstLoop = true;
    for(Node* s: stmtLst) {
        if(isFirstLoop){
            firstSetOfNodes = CFGConstructor::populateCFG(s,prevNode);
            firstNode = firstSetOfNodes.at(0);
            prevNode = firstSetOfNodes;

            isFirstLoop = false;
        }else {
            prevNode = CFGConstructor::populateCFG(s, prevNode);
        }
    }
    return firstNode;
}

/*
 * returns new CFGNode(s) created in a vector
 */
vector<NodeCFG*> CFGConstructor::populateCFG(Node* currNode, vector<NodeCFG*> prevSetOfNodes) {
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
        for (Node *s: stmtLst) {
            newSetOfNodes = populateCFG(s,newSetOfNodes );
            if(isFirstLoop){
                newCFGNode->setNodeInLoop(newSetOfNodes.at(0));
                isFirstLoop = false;
            }
        }
        //last node in while loop to point towards initial LoopCFG
        newSetOfNodes.at(0)->setNextNode(newCFGNode);

        return newSetOfNodes;
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
        newSetOfNodes.push_back(newCFGNode);

        bool isThenBranchFirstLoop = true;
        for (Node *s: thenBranch) {
            newSetOfNodes = populateCFG(s,newSetOfNodes );
            if(isThenBranchFirstLoop){
                for (NodeCFG *t: newSetOfNodes) {

                    newCFGNode->setLeftNode(t);
                }
                isThenBranchFirstLoop = false;
            }
        }
        bool isElseBranchFirstLoop = true;
        for (Node *s: elseBranch) {
            newSetOfNodes = populateCFG(s,newSetOfNodes );
            if(isElseBranchFirstLoop){
                for (NodeCFG *t: newSetOfNodes) {

                    newCFGNode->setRightNode(t);
                }
                isElseBranchFirstLoop = false;
            }
        }

        return newSetOfNodes;

    }else{
        auto* newCFGNode = new NodeCFG(currNode->getStmtNumber());
        if (!prevSetOfNodes.empty()) {
            for (NodeCFG *s: prevSetOfNodes) {
                newCFGNode->setAllPreviousNodes(s->getAllPreviousNode());
                s->setNextNode(newCFGNode);
            }
        }
        newSetOfNodes.push_back(newCFGNode);

    return newSetOfNodes;
    }
}

