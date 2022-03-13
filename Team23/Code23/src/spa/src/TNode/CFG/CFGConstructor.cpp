//
// Created by Lucas Tai on 12/3/22.
//

#include "CFGConstructor.h"
#include "NodeCFG.h"
#include "TNode/WhileNode.h"
#include "TNode/IfNode.h"
vector<NodeCFG*>* CFGConstructor::createCFG(ProcedureNode p) {
    vector<Node*> stmtLst = p.getStmtLst();
    unordered_map<int, NodeCFG *> currMapOfPrevNodes;
    vector<NodeCFG*>* prevNode = nullptr;
    vector<NodeCFG*>* firstSetOfNodes = nullptr;
    bool isFirstLoop = true;
    for(Node* s: stmtLst) {
        if(isFirstLoop){
            firstSetOfNodes = CFGConstructor::populateCFG(s,prevNode);
            isFirstLoop = false;
        }else {
            prevNode = CFGConstructor::populateCFG(s, prevNode);
        }
    }
    return firstSetOfNodes;
}

/*
 * returns new CFGNode created
 */
vector<NodeCFG*>* CFGConstructor::populateCFG(Node* currNode, vector<NodeCFG*>* prevSetOfNodes) {
    vector<NodeCFG*>* newSetOfNodes;
    if(auto value = dynamic_cast<WhileNode*>(currNode)) {
        LoopCFG newCFGNode = LoopCFG(currNode->getStmtNumber());
        if (prevSetOfNodes != nullptr) {
            for (NodeCFG *s: *prevSetOfNodes) {
                newCFGNode.setAllPreviousNodes(s->getAllPreviousNode());
                newCFGNode.addPreviousNode(s);
                s->setNextNode(&newCFGNode);
            }
        }

        vector<Node *> stmtLst = value->getStmtLst();
        newSetOfNodes->push_back(&newCFGNode);
        bool isFirstLoop = true;
        for (Node *s: stmtLst) {
            newSetOfNodes = populateCFG(s,newSetOfNodes );
            if(isFirstLoop){
                newCFGNode.setNodeInLoop(newSetOfNodes);
                isFirstLoop = false;
            }
        }
        return newSetOfNodes;
    }else if(auto value = dynamic_cast<IfNode*>(currNode)) {
        BranchCFG newCFGNode = BranchCFG(currNode->getStmtNumber());
        if (prevSetOfNodes != nullptr) {
            for (NodeCFG *s: *prevSetOfNodes) {
                newCFGNode.setAllPreviousNodes(s->getAllPreviousNode());
                newCFGNode.addPreviousNode(s);
                s->setNextNode(&newCFGNode);
            }
        }

        vector<Node *> thenBranch = value->getThenStmtLst();
        vector<Node *> elseBranch = value->getElseStmtLst();
        newSetOfNodes->push_back(&newCFGNode);

        bool isThenBranchFirstLoop = true;
        for (Node *s: thenBranch) {
            newSetOfNodes = populateCFG(s,newSetOfNodes );
            if(isThenBranchFirstLoop){
                for (NodeCFG *s: *newSetOfNodes) {

                    newCFGNode.setLeftNode(&newCFGNode);
                }
                isThenBranchFirstLoop = false;
            }
        }
        bool isElseBranchFirstLoop = true;
        for (Node *s: elseBranch) {
            newSetOfNodes = populateCFG(s,newSetOfNodes );
            if(isElseBranchFirstLoop){
                for (NodeCFG *s: *newSetOfNodes) {

                    newCFGNode.setLeftNode(&newCFGNode);
                }
                isElseBranchFirstLoop = false;
            }
        }

        return newSetOfNodes;

    }else{
        NodeCFG newCFGNode = NodeCFG(currNode->getStmtNumber());

        if (prevSetOfNodes != nullptr) {
            for (NodeCFG *s: *prevSetOfNodes) {
                newCFGNode.setAllPreviousNodes(s->getAllPreviousNode());
                newCFGNode.addPreviousNode(s);
                s->setNextNode(&newCFGNode);
            }
        }
        newSetOfNodes->push_back(&newCFGNode);
        return newSetOfNodes;
    }
}

