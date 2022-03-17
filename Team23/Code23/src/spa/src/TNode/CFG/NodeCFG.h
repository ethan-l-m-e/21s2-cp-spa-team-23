//
// Created by Tin Hong Wen on 4/3/22.
//

#ifndef SPA_NODECFG_H
#define SPA_NODECFG_H

#include <string>
#include <unordered_map>
using namespace std;

#define nullStmtNo 0

class NodeCFG {
protected:
    int statementNumber;
    NodeCFG* nextNode;
    unordered_map<int, NodeCFG*> mapOfPreviousNodes;
public:
    NodeCFG(int statementNumber);
    int getStatementNumber();

    void setNextNode(NodeCFG* node);
    void addPreviousNode(NodeCFG* node);
    NodeCFG* getNextNode();
    unordered_map<int, NodeCFG*> getAllPreviousNode();

    NodeCFG* getStartNode();
    virtual NodeCFG* getEndNode();
    virtual bool isStart();

    virtual bool isEnd();

    void setAllPreviousNodes(unordered_map<int, NodeCFG *> allPrevNodesMap);
};


class BranchCFG: public NodeCFG {
protected:
    NodeCFG* rightNode;
    NodeCFG* leftNode;
public:
    BranchCFG(int statementNumber);
    void setLeftNode(NodeCFG* node);
    void setRightNode(NodeCFG* node);
    NodeCFG* getLeftNode();
    NodeCFG* getRightNode();

    NodeCFG* getLastLeftNode();
    NodeCFG* getLastRightNode();

    bool isEnd();
};

class LoopCFG: public NodeCFG {
protected:
    NodeCFG* nodeInLoop;
public:
    LoopCFG(int statementNumber);
    void setNodeInLoop(NodeCFG* node);
    NodeCFG* getNodeInLoop();
    bool isStart() override;
};
#endif //SPA_NODECFG_H
