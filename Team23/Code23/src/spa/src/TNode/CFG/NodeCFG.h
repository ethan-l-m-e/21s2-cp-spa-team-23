//
// Created by Tin Hong Wen on 4/3/22.
//

#ifndef SPA_NODECFG_H
#define SPA_NODECFG_H

#include <string>

using namespace std;

#define nullStmtNo 0

class NodeCFG {
protected:
    int statementNumber;
    NodeCFG* nextNode;
    NodeCFG* previousNode;
public:
    NodeCFG(int statementNumber);
    int getStatementNumber();

    void setNextNode(NodeCFG* node);
    void setPreviousNode(NodeCFG* node);
    NodeCFG* getNextNode();
    NodeCFG* getPreviousNode();

    NodeCFG* getStartNode();
    virtual NodeCFG* getEndNode();
    bool isStart();
    bool isEnd();
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
};

class MergeCFG: public NodeCFG {
protected:
    NodeCFG* leftPreviousNode;
    NodeCFG* rightPreviousNode;

public:
    MergeCFG(int statementNumber);
    void setLeftPreviousNode(NodeCFG* node);
    void setRightPreviousNode(NodeCFG* node);
    NodeCFG* getLeftPreviousNode();
    NodeCFG* getRightPreviousNode();
};

class ImagineMergeCFG: public MergeCFG {
public:
    ImagineMergeCFG(): MergeCFG(nullStmtNo) {}
    NodeCFG* getEndNode() override;
};


class LoopCFG: NodeCFG {
protected:
    NodeCFG* nodeInLoop;
public:
    LoopCFG(int statementNumber);
    void setNodeInLoop(NodeCFG* node);
    NodeCFG* getNodeInLoop();
};
#endif //SPA_NODECFG_H
